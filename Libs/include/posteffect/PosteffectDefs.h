#if !defined(__IZANAGI_POSTEFFECT_DEFS_H__)
#define __IZANAGI_POSTEFFECT_DEFS_H__

#include "izD3DDefs.h"
#include "izStd.h"
#include "graph/GraphDefs.h"

#define IZ_POSTEFFECT_PARAM_TYPE(flag, row, column, is_int, is_float)\
	((((flag) & 0x0f) << 10) | (((row) & 0x0f) << 6) | (((column) & 0x0f) << 2) | (((is_int) & 0x01) << 1) | ((is_float) & 0x01))

#define IZ_GET_FLAG_POSTEFFECT_PARAM_TYPE(type)\
	(((type) >> 10) & 0x0f)

#define IZ_GET_ROW_POSTEFFECT_PARAM_TYPE(type)\
	(((type) >> 6) & 0x0f)

#define IZ_GET_COLUMN_POSTEFFECT_PARAM_TYPE(type)\
	(((type) >> 2) & 0x0f)

#define IZ_IS_INT_POSTEFFECT_PARAM_TYPE(type)\
	(((type) >> 1) & 0x01)

#define IZ_IS_FLOAT_POSTEFFECT_PARAM_TYPE(type)\
	((type) & 0x01)

namespace izanagi {
	/**
	* ポストエフェクトパラメータのクラス
	*/
	enum E_POSTEFFECT_PARAMETER_CLASS {
		E_POSTEFFECT_PARAMETER_CLASS_UNKNOWN = 0,	// その他
		E_POSTEFFECT_PARAMETER_CLASS_SCALAR,		// スカラー
		E_POSTEFFECT_PARAMETER_CLASS_VECTOR,		// ベクトル
		E_POSTEFFECT_PARAMETER_CLASS_MATRIX,		// マトリクス
		E_POSTEFFECT_PARAMETER_CLASS_STRUCT,		// 構造体
		E_POSTEFFECT_PARAMETER_CLASS_ARRAY,			// 配列
		E_POSTEFFECT_PARAMETER_CLASS_SAMPLER,		// サンプラ
		E_POSTEFFECT_PARAMETER_CLASS_OBJECT,		// テクスチャ、シェーダ、または文字列
		
		E_POSTEFFECT_PARAMETER_CLASS_NUM,			// パラメータのクラス数の定義

		E_POSTEFFECT_PARAMETER_CLASS_FORCE_INT32 = 0x7fffffff,	// enum のサイズを IZ_INT と同じにするため
	};

	/**
	* ポストエフェクトパラメータのタイプ
	*/
	enum E_POSTEFFECT_PARAMETER_TYPE {
		E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG = 0,
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG,
		E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG,
		E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG,
		E_POSTEFFECT_PARAMETER_TYPE_STRING_FLAG,
		E_POSTEFFECT_PARAMETER_TYPE_TEXTURE_FLAG,
		E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG,

		E_POSTEFFECT_PARAMETER_TYPE_HALF	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_HALF1x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF1x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF1x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF1x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 1, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_HALF2x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 2, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF2x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 2, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF2x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 2, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF2x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 2, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_HALF3x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 3, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF3x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 3, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF3x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 3, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF3x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 3, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_HALF4x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 4, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF4x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 4, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF4x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 4, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_HALF4x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_HALF_FLAG, 4, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_FLOAT	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG,  1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_FLOAT1x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT1x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT1x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT1x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 1, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_FLOAT2x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 2, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT2x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 2, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT2x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 2, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT2x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 2, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_FLOAT3x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 3, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT3x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 3, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT3x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 3, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT3x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 3, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_FLOAT4x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 4, 1, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT4x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 4, 2, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT4x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 4, 3, 0, 1),
		E_POSTEFFECT_PARAMETER_TYPE_FLOAT4x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_FLOAT_FLAG, 4, 4, 0, 1),

		E_POSTEFFECT_PARAMETER_TYPE_INT			= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT1		= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT2		= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT3		= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT4		= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_INT1x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT1x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT1x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT1x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 1, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_INT2x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 2, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT2x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 2, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT2x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 2, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT2x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 2, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_INT3x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 3, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT3x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 3, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT3x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 3, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT3x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 3, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_INT4x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 4, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT4x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 4, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT4x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 4, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_INT4x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_INT_FLAG, 4, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_BOOL	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_BOOL1x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL1x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL1x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL1x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 1, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_BOOL2x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 2, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL2x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 2, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL2x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 2, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL2x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 2, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_BOOL3x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 3, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL3x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 3, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL3x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 3, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL3x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 3, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_BOOL4x1	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 4, 1, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL4x2	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 4, 2, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL4x3	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 4, 3, 1, 0),
		E_POSTEFFECT_PARAMETER_TYPE_BOOL4x4	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_BOOL_FLAG, 4, 4, 1, 0),

		E_POSTEFFECT_PARAMETER_TYPE_STRING	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_STRING_FLAG,  0, 0, 0, 0),
		E_POSTEFFECT_PARAMETER_TYPE_TEXTURE	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_TEXTURE_FLAG, 0, 0, 0, 0),

		E_POSTEFFECT_PARAMETER_TYPE_SAMPLER1D	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG, 0, 0, 0, 0),
		E_POSTEFFECT_PARAMETER_TYPE_SAMPLER2D	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG, 0, 0, 0, 0),
		E_POSTEFFECT_PARAMETER_TYPE_SAMPLER3D	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG, 0, 0, 0, 0),
		E_POSTEFFECT_PARAMETER_TYPE_SAMPLERRECT	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG, 0, 0, 0, 0),
		E_POSTEFFECT_PARAMETER_TYPE_SAMPLERCUBE	= IZ_POSTEFFECT_PARAM_TYPE(E_POSTEFFECT_PARAMETER_TYPE_SAMPLER_FLAG, 0, 0, 0, 0),

		E_POSTEFFECT_PARAMETER_TYPE_FORCE_INT32 = 0x7fffffff,
	};

	/**
	* テクスチャタイプ
	*/
	enum E_POSTEFFECT_TEXTURE_TYPE {
		E_POSTEFFECT_TEXTURE_TYPE_NONE = 0,		// NONE,

		E_POSTEFFECT_TEXTURE_TYPE_INPUT_SCENE,	// INPUT_SCENE
		E_POSTEFFECT_TEXTURE_TYPE_INPUT_DEPTH,	// INPUT_DEPTH

		E_POSTEFFECT_TEXTURE_TYPE_PRIVATE,		// PRIVATE
		E_POSTEFFECT_TEXTURE_TYPE_INPUT,		// INPUT

		E_POSTEFFECT_TEXTURE_TYPE_NUM,			// パラメータのタイプ数の定義

		E_POSTEFFECT_TEXTURE_TYPE_FORCE_INT32 = 0x7fffffff,	// enum のサイズを IZ_INT と同じにするため.
	};

	// 頂点シェーダタイプ
	enum E_POSTEFFECT_VTX_SHADER {
		E_POSTEFFECT_VTX_SHADER_SAMPLING_1 = 0,	// １点をサンプリング（デフォルト）
		E_POSTEFFECT_VTX_SHADER_SAMPLING_4,		// 周囲４点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_8,		// 周囲８点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_16,	// 周囲１６点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_5,		// 周囲５点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_7,		// 周囲７点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_9,		// 周囲９点をサンプリング
		E_POSTEFFECT_VTX_SHADER_SAMPLING_13,	// 周囲１３点をサンプリング

		E_POSTEFFECT_VTX_SHADER_NUM,

		E_POSTEFFECT_VTX_SHADER_FORCE_INT32 = 0x7fffffff,
	};

	typedef IZ_UINT	IZ_POSTEFFECT_HANDLE;
	enum {
		IZ_POSTEFFECT_HANDLE_INVALID = 0x7fffffff,
	};
}	// namespace

#endif	// #if !defined(__IZANAGI_POSTEFFECT_DEFS_H__)
