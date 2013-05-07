﻿//#define ENABLE_DEBUG_MSG

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Reflection;

namespace ShaderCompiler
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Compiler.Do(args);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }

    static public unsafe class Compiler
    {
        /// <summary>
        /// 使い方を表示
        /// </summary>
        static void DisplayUsage()
        {
            Console.WriteLine("Usage : ShaderCompiler <options>");
            Console.WriteLine();
            Console.WriteLine("options ****");
            Console.WriteLine("-i <input>");
            Console.WriteLine("-o <output>");
            Console.WriteLine("-e <etnry>");
            Console.WriteLine("-p <profile>");
            Console.WriteLine("-I <includes>");
            Console.WriteLine("-D <defines>");
            Console.WriteLine("--string-table");
            Console.WriteLine("-opt <options> : options for native compiler (fxc.exe)");
        }

        /// <summary>
        /// Preproc.exe のプロセスを実行するための準備
        /// </summary>
        /// <param name="option"></param>
        /// <param name="enableLineDirectives"></param>
        /// <returns>Preproc.exe のプロセス開始情報</returns>
        static ProcessStartInfo PrepareProcessPreproc(
            Option option,
            bool enableLineDirectives)
        {
            // NOTE
            // Preproc.exe は実行ファイルと同じパスにあること

            var asm = Assembly.GetEntryAssembly();
            string path = asm.Location;

            var preproc = Path.GetDirectoryName(path);
            preproc = Path.Combine(preproc, "Preproc.exe");

            if (!File.Exists(preproc))
            {
                // TODO
                throw new Exception();
            }

            string args = "";

            if (!string.IsNullOrEmpty(option.Includes))
            {
                args += "-I" + " " + option.Includes;
            }

            if (!string.IsNullOrEmpty(option.Defines))
            {
                args += "-D" + " " + option.Defines;
            }

            if (!enableLineDirectives)
            {
                args += " " + "-EP";
            }

            args += " " + option.Input;
            args += " " + option.PreprocessedFile;

            ProcessStartInfo info = new ProcessStartInfo();

            info.FileName = preproc;

            info.Arguments = args;

            info.CreateNoWindow = true;
            info.RedirectStandardOutput = true;
            info.RedirectStandardError = false;
            info.UseShellExecute = false;

            return info;
        }

        /// <summary>
        /// Preproc.exe を実行
        /// </summary>
        /// <param name="option"></param>
        /// <param name="enableLineDirectives"></param>
        static void RunPreprocess(
            Option option,
            bool enableLineDirectives = true)
        {
            var process = new Process();

            process.StartInfo = PrepareProcessPreproc(option, enableLineDirectives);

            DebugWriteLine("{0} {1}", process.StartInfo.FileName, process.StartInfo.Arguments);

            process.Start();
            process.WaitForExit();
        }

        /// <summary>
        /// fxc.exe のプロセスを実行するための準備
        /// </summary>
        /// <param name="option"></param>
        /// <returns>fxc.exe のプロセス開始情報</returns>
        static ProcessStartInfo PrepareProcessFxc(Option option)
        {
            // DXSDKのディレクトリのパスを環境変数より取得
            var dxDir = System.Environment.GetEnvironmentVariable("DXSDK_DIR");
            if (string.IsNullOrEmpty(dxDir))
            {
                return null;
            }

            ProcessStartInfo info = new ProcessStartInfo();

            // fxc.exe のパス
            info.FileName = Path.Combine(dxDir, @"Utilities\bin\x64", "fxc.exe");

            info.Arguments = "/nologo";
            info.Arguments += " " + "/Fo" + " " + option.ByteCodedFile;
            info.Arguments += " " + "/E" + " " + option.Entry;
            info.Arguments += " " + "/T" + " " + option.Profile;
            info.Arguments += " " + option.PreprocessedFile;

            info.CreateNoWindow = true;
            info.RedirectStandardOutput = true;
            info.RedirectStandardError = true;
            info.UseShellExecute = false;

            return info;
        }

        /// <summary>
        /// fxc.exe を実行
        /// </summary>
        /// <param name="option"></param>
        static void RunFxc(Option option)
        {
            var process = new Process();

            process.StartInfo = PrepareProcessFxc(option);

            DebugWriteLine("{0} {1}", process.StartInfo.FileName, process.StartInfo.Arguments);

            process.Start();
            process.WaitForExit();

            var output = process.StandardError.ReadToEnd();

            Console.WriteLine(output);
        }

        static public void Do(string[] args)
        {
            var option = new Option(args);

            if (!option.IsValid)
            {
                DisplayUsage();
                return;
            }

            RunPreprocess(option);
            RunFxc(option);

            char* bytecode = (char*)System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(option.ByteCodedFile);

            var dir = Path.GetDirectoryName(option.Input);

            var tmp = DateTime.Now.ToString("yyyy_MM_dd_HH_mm_ss") + ".txt";
            tmp = Path.Combine(dir, tmp);

            DebugWriteLine("{0}", tmp);

            char* output = (char*)System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(tmp);

            bool result = izanagi.tool.MojoShaderProxy.Parse((sbyte*)bytecode, (sbyte*)output);

            DebugWriteLine("{0}", result ? "Succeeded" : "Failed");

            if (result)
            {
                DebugWriteLine("Export to [{0}]", option.Output);

                // TODO
                // For GLESSL

#if true
                var preprocessed = tmp + ".pp";

                RunPreprocess(
                    new Option()
                    {
                        Input = tmp,
                        PreprocessedFile = preprocessed,
                    });

                File.Delete(tmp);

                tmp = preprocessed;
#endif

                int count = 0;

                using (var sr = new StreamReader(tmp, Encoding.ASCII))
                {
                    using (var sw = new StreamWriter(option.Output, false, Encoding.ASCII))
                    {
                        if (option.IsExportAsStringTable)
                        {
                            sw.WriteLine("const char* " + option.Entry + " = {");
                        }

                        while (sr.Peek() >= 0)
                        {
                            var line = sr.ReadLine();
                            if (count == 0)
                            {
                                WriteLine(option, sw, "precision highp float;");
                                WriteLine(option, sw, "");
                            }
                            else
                            {
                                WriteLine(option, sw, line);
                            }
                            count++;
                        }

                        if (option.IsExportAsStringTable)
                        {
                            sw.WriteLine("};");
                        }
                    }
                }
            }

            File.Delete(tmp);
        }

        static void WriteLine(Option option, StreamWriter sw, string line)
        {
            string output = line;

            if (option.IsExportAsStringTable)
            {
                output = string.Format("\"{0}\\n\"", line);
            }

            sw.WriteLine(output);
        }

        static void DebugWriteLine(string format, params object[] args)
        {
#if ENABLE_DEBUG_MSG
            var msg = string.Format(format, args);
            DebugWriteLine(msg);
#endif
        }

        static void DebugWriteLine(string msg)
        {
#if ENABLE_DEBUG_MSG
            Console.WriteLine(msg);
#endif
        }
    }

    /// <summary>
    /// オプション
    /// </summary>
    class Option
    {
        /// <summary>
        /// 入力ファイル名
        /// </summary>
        public string Input;

        /// <summary>
        /// 出力ファイル名
        /// </summary>
        public string Output;

        /// <summary>
        /// エントリポイント
        /// </summary>
        public string Entry;

        /// <summary>
        /// プロファイル（vs_2_0, ps_2_0 など）
        /// </summary>
        public string Profile;

        /// <summary>
        /// プリプロセスされたファイル名
        /// </summary>
        public string PreprocessedFile;

        /// <summary>
        /// バイトコード出力されたファイル名
        /// </summary>
        public string ByteCodedFile;

        /// <summary>
        /// インクルードパス指定
        /// </summary>
        public string Includes;

        /// <summary>
        /// デファイン指定
        /// </summary>
        public string Defines;

        /// <summary>
        /// fxc.exe に直接設定するオプション
        /// </summary>
        public string Options;

        /// <summary>
        /// 文字列テーブルとして出力するかどうか
        /// </summary>
        public bool IsExportAsStringTable;

        public Option(string[] args)
        {
            bool isOptions = false;
            bool isIncludes = false;
            bool isDefines = false;

            for (int i = 0; i < args.Length; i++)
            {
                var arg = args[i];

                if (arg == "-opt")
                {
                    isOptions = true;
                }
                else if (arg == "-I")
                {
                    isIncludes = true;
                }
                else if (arg == "-D")
                {
                    isDefines = true;
                }
                else if (arg == "-i")
                {
                    this.Input = args[++i];
                }
                else if (arg == "-o")
                {
                    this.Output = args[++i];
                }
                else if (arg == "-e")
                {
                    this.Entry = args[++i];
                }
                else if (arg == "-p")
                {
                    this.Profile = args[++i];
                }
                else if (arg == "--string-table")
                {
                    this.IsExportAsStringTable = true;
                }
                else if (isOptions)
                {
                    if (string.IsNullOrEmpty(this.Options))
                    {
                        this.Options = arg;
                    }
                    else
                    {
                        this.Options += " " + arg;
                    }
                }
                else if (isIncludes)
                {
                    if (string.IsNullOrEmpty(this.Includes))
                    {
                        this.Includes = arg;
                    }
                    else
                    {
                        this.Includes += " " + arg;
                    }
                }
                else if (isDefines)
                {
                    if (string.IsNullOrEmpty(this.Defines))
                    {
                        this.Defines = arg;
                    }
                    else
                    {
                        this.Defines += " " + arg;
                    }
                }
            }

            // 入力ファイル名からプリプロセスされたファイル名とバイトコード出力されたファイル名を作成する
            if (!string.IsNullOrEmpty(this.Input))
            {
                var dir = Path.GetDirectoryName(this.Input);
                this.ByteCodedFile = Path.GetFileNameWithoutExtension(this.Input);
                this.ByteCodedFile = Path.Combine(dir, this.ByteCodedFile);
                this.ByteCodedFile += ".bc";

                this.PreprocessedFile = this.Input + "_";
            }
        }

        public Option()
        {
        }

        public bool IsValid
        {
            get
            {
                bool isInvalid = string.IsNullOrEmpty(this.Entry)
                    || string.IsNullOrEmpty(this.Profile)
                    || string.IsNullOrEmpty(this.Output)
                    || string.IsNullOrEmpty(this.Input)
                    || string.IsNullOrEmpty(this.ByteCodedFile)
                    || string.IsNullOrEmpty(this.PreprocessedFile);

                return !isInvalid;
            }
        }
    }
}
