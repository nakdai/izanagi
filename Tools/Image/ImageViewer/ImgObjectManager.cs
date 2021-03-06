﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ImageViewer
{
    /// <summary>
    /// 作成されたイメージデータを管理しておく
    /// </summary>
    class ImgObjectManager : Dictionary<int, IImgObject>
    {
        static private ImgObjectManager instance = new ImgObjectManager();

        static public ImgObjectManager Instance
        {
            get
            {
                return instance;
            }
        }

        private ImgObjectManager()
        {
        }

        /// <summary>
        /// 作成されたイメージデータを保存する
        /// </summary>
        /// <param name="imgMaster">保存したいイメージマスタ</param>
        public void Register(ImgMaster imgMaster)
        {
            this.Add(imgMaster.ID, imgMaster);

            foreach (var tex in imgMaster.GetTexture())
            {
                this.Add(tex.ID, tex);

                foreach (var img in tex.GetImage())
                {
                    this.Add(img.ID, img);
                }
            }
        }
    }
}
