/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2025 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 */

#ifndef __pspgup_h__
#define __pspgup_h__

#include <psptypes.h>
#include <pspge.h>
#include <math.h>

/** @defgroup GU Graphics Utility Library
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* PI, float-sized */
#define GU_PI			(3.141593f)

/* Boolean values for convenience */
#define GU_FALSE		(0)
#define GU_TRUE			(1)

/* Primitive types */
#define GU_POINTS		(0)
#define GU_LINES		(1)
#define GU_LINE_STRIP		(2)
#define GU_TRIANGLES		(3)
#define GU_TRIANGLE_STRIP	(4)
#define GU_TRIANGLE_FAN		(5)
#define GU_SPRITES		(6)

/* States */
#define GU_ALPHA_TEST		(0)
#define GU_DEPTH_TEST		(1)
#define GU_SCISSOR_TEST		(2)
#define GU_STENCIL_TEST		(3)
#define GU_BLEND		(4)
#define GU_CULL_FACE		(5)
#define GU_DITHER		(6)
#define GU_FOG			(7)
#define GU_CLIP_PLANES		(8)
#define GU_TEXTURE_2D		(9)
#define GU_LIGHTING		(10)
#define GU_LIGHT0		(11)
#define GU_LIGHT1		(12)
#define GU_LIGHT2		(13)
#define GU_LIGHT3		(14)
#define GU_LINE_SMOOTH		(15)
#define GU_PATCH_CULL_FACE	(16)
#define GU_COLOR_TEST		(17)
#define GU_COLOR_LOGIC_OP	(18)
#define GU_FACE_NORMAL_REVERSE	(19)
#define GU_PATCH_FACE		(20)
#define GU_COLOR_DOUBLE		(21)
#define GU_MAX_STATUS		(22)

/* Matrix modes */
#define GU_PROJECTION		(0)
#define GU_VIEW			(1)
#define GU_MODEL		(2)
#define GU_TEXTURE		(3)

/* Vertex Declarations Begin */
#define GU_TEXTURE_SHIFT(n)	((n)<<0)
#define GU_TEXTURE_8BIT		GU_TEXTURE_SHIFT(1)
#define GU_TEXTURE_16BIT	GU_TEXTURE_SHIFT(2)
#define GU_TEXTURE_32BITF	GU_TEXTURE_SHIFT(3)
#define GU_TEXTURE_BITS		GU_TEXTURE_SHIFT(3)

#define GU_COLOR_SHIFT(n)	((n)<<2)
#define GU_COLOR_5650		GU_COLOR_SHIFT(4)
#define GU_COLOR_5551		GU_COLOR_SHIFT(5)
#define GU_COLOR_4444		GU_COLOR_SHIFT(6)
#define GU_COLOR_8888		GU_COLOR_SHIFT(7)
#define GU_COLOR_BITS		GU_COLOR_SHIFT(7)

#define GU_NORMAL_SHIFT(n)	((n)<<5)
#define GU_NORMAL_8BIT		GU_NORMAL_SHIFT(1)
#define GU_NORMAL_16BIT		GU_NORMAL_SHIFT(2)
#define GU_NORMAL_32BITF	GU_NORMAL_SHIFT(3)
#define GU_NORMAL_BITS		GU_NORMAL_SHIFT(3)

#define GU_VERTEX_SHIFT(n)	((n)<<7)
#define GU_VERTEX_8BIT		GU_VERTEX_SHIFT(1)
#define GU_VERTEX_16BIT		GU_VERTEX_SHIFT(2)
#define GU_VERTEX_32BITF	GU_VERTEX_SHIFT(3)
#define GU_VERTEX_BITS		GU_VERTEX_SHIFT(3)

#define GU_WEIGHT_SHIFT(n)	((n)<<9)
#define GU_WEIGHT_8BIT		GU_WEIGHT_SHIFT(1)
#define GU_WEIGHT_16BIT		GU_WEIGHT_SHIFT(2)
#define GU_WEIGHT_32BITF	GU_WEIGHT_SHIFT(3)
#define GU_WEIGHT_BITS		GU_WEIGHT_SHIFT(3)

#define GU_INDEX_SHIFT(n)	((n)<<11)
#define GU_INDEX_8BIT		GU_INDEX_SHIFT(1)
#define GU_INDEX_16BIT		GU_INDEX_SHIFT(2)
#define GU_INDEX_BITS		GU_INDEX_SHIFT(3)

#define GU_WEIGHTS(n)		((((n)-1)&7)<<14)
#define GU_WEIGHTS_BITS		GU_WEIGHTS(8)
#define GU_VERTICES(n)		((((n)-1)&7)<<18)
#define GU_VERTICES_BITS	GU_VERTICES(8)

#define GU_TRANSFORM_SHIFT(n)	((n)<<23)
#define GU_TRANSFORM_3D		GU_TRANSFORM_SHIFT(0)
#define GU_TRANSFORM_2D		GU_TRANSFORM_SHIFT(1)
#define GU_TRANSFORM_BITS	GU_TRANSFORM_SHIFT(1)
/* Vertex Declarations End */

/* display ON/OFF switch */
#define GU_DISPLAY_OFF		0
#define GU_DISPLAY_ON		1

/* screen size */
#define GU_SCR_WIDTH       480
#define GU_SCR_HEIGHT      272
#define GU_SCR_ASPECT      ((float)GU_SCR_WIDTH / (float)GU_SCR_HEIGHT)
#define GU_SCR_OFFSETX     ((4096 - GU_SCR_WIDTH) / 2)
#define GU_SCR_OFFSETY     ((4096 - GU_SCR_HEIGHT) / 2)

/* Frame buffer */
#define GU_VRAM_TOP        0x00000000
#define GU_VRAM_WIDTH      512
/* 16bit mode */
#define GU_VRAM_BUFSIZE    (GU_VRAM_WIDTH*GU_SCR_HEIGHT*2)
#define GU_VRAM_BP_0       (void *)(GU_VRAM_TOP)
#define GU_VRAM_BP_1       (void *)(GU_VRAM_TOP+GU_VRAM_BUFSIZE)
#define GU_VRAM_BP_2       (void *)(GU_VRAM_TOP+(GU_VRAM_BUFSIZE*2))
/* 32bit mode */
#define GU_VRAM_BUFSIZE32  (GU_VRAM_WIDTH*GU_SCR_HEIGHT*4)
#define GU_VRAM_BP32_0     (void *)(GU_VRAM_TOP)
#define GU_VRAM_BP32_1     (void *)(GU_VRAM_TOP+GU_VRAM_BUFSIZE32)
#define GU_VRAM_BP32_2     (void *)(GU_VRAM_TOP+(GU_VRAM_BUFSIZE32*2))

/* Pixel Formats */
#define GU_PSM_5650		(0) /* Display, Texture, Palette */
#define GU_PSM_5551		(1) /* Display, Texture, Palette */
#define GU_PSM_4444		(2) /* Display, Texture, Palette */
#define GU_PSM_8888		(3) /* Display, Texture, Palette */
#define GU_PSM_T4		(4) /* Texture */
#define GU_PSM_T8		(5) /* Texture */
#define GU_PSM_T16		(6) /* Texture */
#define GU_PSM_T32		(7) /* Texture */
#define GU_PSM_DXT1		(8) /* Texture */
#define GU_PSM_DXT3		(9) /* Texture */
#define GU_PSM_DXT5		(10) /* Texture */

/* Spline Mode */
#define GU_FILL_FILL	(0)
#define GU_OPEN_FILL	(1)
#define GU_FILL_OPEN	(2)
#define GU_OPEN_OPEN	(3)

/* Shading Model */
#define GU_FLAT			(0)
#define GU_SMOOTH		(1)

/* Logical operation */
#define GU_CLEAR		(0)
#define GU_AND			(1)
#define GU_AND_REVERSE		(2)
#define GU_COPY			(3)
#define GU_AND_INVERTED		(4)
#define GU_NOOP			(5)
#define GU_XOR			(6)
#define GU_OR			(7)
#define GU_NOR			(8)
#define GU_EQUIV		(9)
#define GU_INVERTED		(10)
#define GU_OR_REVERSE		(11)
#define GU_COPY_INVERTED	(12)
#define GU_OR_INVERTED		(13)
#define GU_NAND			(14)
#define GU_SET			(15)

/* Texture Filter */
#define GU_NEAREST		(0)
#define GU_LINEAR		(1)
#define GU_NEAREST_MIPMAP_NEAREST (4)
#define GU_LINEAR_MIPMAP_NEAREST (5)
#define GU_NEAREST_MIPMAP_LINEAR (6)
#define GU_LINEAR_MIPMAP_LINEAR	(7)

/* Texture Map Mode */
#define GU_TEXTURE_COORDS	(0)
#define GU_TEXTURE_MATRIX	(1)
#define GU_ENVIRONMENT_MAP	(2)

/* Texture Level Mode */
#define GU_TEXTURE_AUTO		(0)
#define GU_TEXTURE_CONST	(1)
#define GU_TEXTURE_SLOPE	(2)

/* Texture Projection Map Mode */
#define GU_POSITION		(0)
#define GU_UV			(1)
#define GU_NORMALIZED_NORMAL	(2)
#define GU_NORMAL		(3)

/* Wrap Mode */
#define GU_REPEAT		(0)
#define GU_CLAMP		(1)

/* Front Face Direction */
#define GU_CW			(0)
#define GU_CCW			(1)

/* Test Function */
#define GU_NEVER		(0)
#define GU_ALWAYS		(1)
#define GU_EQUAL		(2)
#define GU_NOTEQUAL		(3)
#define GU_LESS			(4)
#define GU_LEQUAL		(5)
#define GU_GREATER		(6)
#define GU_GEQUAL		(7)

/* Clear Buffer Mask */
#define GU_COLOR_BUFFER_BIT	(1)
#define GU_STENCIL_BUFFER_BIT	(2)
#define GU_DEPTH_BUFFER_BIT	(4)
#define GU_FAST_CLEAR_BIT	(16)

/* Texture Effect */
#define GU_TFX_MODULATE		(0)
#define GU_TFX_DECAL		(1)
#define GU_TFX_BLEND		(2)
#define GU_TFX_REPLACE		(3)
#define GU_TFX_ADD		(4)

/* Texture Color Component */
#define GU_TCC_RGB		(0)
#define GU_TCC_RGBA		(1)

/* Blending Op */
#define GU_ADD			(0)
#define GU_SUBTRACT		(1)
#define GU_REVERSE_SUBTRACT	(2)
#define GU_MIN			(3)
#define GU_MAX			(4)
#define GU_ABS			(5)

/* Blending Factor */
#define GU_SRC_COLOR		(0)
#define GU_ONE_MINUS_SRC_COLOR	(1)
#define GU_SRC_ALPHA		(2)
#define GU_ONE_MINUS_SRC_ALPHA	(3)
#define GU_DST_COLOR		(0)
#define GU_ONE_MINUS_DST_COLOR	(1)
#define GU_DST_ALPHA		(4)
#define GU_ONE_MINUS_DST_ALPHA	(5)
#define GU_FIX			(10)

/* Stencil Operations */
#define GU_KEEP			(0)
#define GU_ZERO			(1)
#define GU_REPLACE		(2)
#define GU_INVERT		(3)
#define GU_INCR			(4)
#define GU_DECR			(5)

/* Light Components */
#define GU_AMBIENT		(1)
#define GU_DIFFUSE		(2)
#define GU_SPECULAR		(4)
#define GU_AMBIENT_AND_DIFFUSE	(GU_AMBIENT|GU_DIFFUSE)
#define GU_DIFFUSE_AND_SPECULAR	(GU_DIFFUSE|GU_SPECULAR)
#define GU_UNKNOWN_LIGHT_COMPONENT (8)

/* Light modes */
#define GU_SINGLE_COLOR		(0)
#define GU_SEPARATE_SPECULAR_COLOR (1)

/* Light Type */
#define GU_DIRECTIONAL		(0)
#define GU_POINTLIGHT		(1)
#define GU_SPOTLIGHT		(2)

/* Contexts */
#define GU_DIRECT		(0)
#define GU_CALL			(1)
#define GU_SEND			(2)

/* List Queue */
#define GU_TAIL			(0)
#define GU_HEAD			(1)

/* Sync behavior (mode) */
#define GU_SYNC_FINISH	(0)
#define GU_SYNC_SIGNAL	(1)
#define GU_SYNC_DONE	(2)
#define GU_SYNC_LIST	(3)
#define GU_SYNC_SEND	(4)

/* behavior (what) */
#define GU_SYNC_WAIT	(0)
#define GU_SYNC_NOWAIT	(1)

/* Sync behavior (what) [see pspge.h] */
#define GU_SYNC_WHAT_DONE (0)
#define GU_SYNC_WHAT_QUEUED (1)
#define GU_SYNC_WHAT_DRAW (2)
#define GU_SYNC_WHAT_STALL (3)
#define GU_SYNC_WHAT_CANCEL (4)

/* Call mode */
#define GU_CALL_NORMAL (0)
#define GU_CALL_SIGNAL (1)

/* Signal models */
#define GU_SIGNAL_WAIT (1)
#define GU_SIGNAL_NOWAIT (2)
#define GU_SIGNAL_PAUSE (3)

/* Signals */
#define GU_CALLBACK_SIGNAL	(1)
#define GU_CALLBACK_FINISH	(4)

/* Signal behavior */
#define GU_BEHAVIOR_SUSPEND (1)
#define GU_BEHAVIOR_CONTINUE (2)

/* Break mode */
#define GU_BREAK_PAUSE (0)
#define GU_BREAK_CANCEL (1)

/* Color Macros, maps 8 bit unsigned channels into one 32-bit value */
#define GU_ABGR(a,b,g,r)	(((a) << 24)|((b) << 16)|((g) << 8)|(r))
#define GU_ARGB(a,r,g,b)	GU_ABGR((a),(b),(g),(r))
#define GU_RGBA(r,g,b,a)	GU_ARGB((a),(r),(g),(b))

/* Color Macro, maps floating point channels (0..1) into one 32-bit value */
#define GU_COLOR(r,g,b,a)	GU_RGBA((u32)((r) * 255.0f),(u32)((g) * 255.0f),(u32)((b) * 255.0f),(u32)((a) * 255.0f))





typedef enum GECommand
{
	/* No operation */
	NOP = 0x0,			
	/* Vertex data */
	VADDR = 0x1,		
	/* Index data */
	IADDR = 0x2,		
	/* Draw Primitive */
	PRIM = 0x4,			
	/* Draw Bezier surface */
	BEZIER = 0x5,		
	/* Draw Spline surface */
	SPLINE = 0x6,		
	/* Bounding Box */
	BOUNDING_BOX = 0x7, 
	/* Jump */
	JUMP = 0x8,			
	/* Conditional Jump */
	BJUMP = 0x9,		
	/* List Call */
	CALL = 0xa,			
	/* List Return */
	RET = 0xb,			
	/* End reading */
	END = 0xc,			
	/* Signal interrupt */
	SIGNAL = 0xe,		
	/* Finish drawing */
	FINISH = 0xf,		
	/* Address base */
	BASE = 0x10,		
	/* Vertex type */
	VERTEX_TYPE = 0x12, 
	/* Offset address */
	OFFSET_ADDR = 0x13, 
	/* Origin address */
	ORIGIN = 0x14,		
	/* Drawing region 1, origin */
	REGION1 = 0x15,		
	/* Drawing region 2, end */
	REGION2 = 0x16,		

	/* Lighting enable */
	LIGHTING_ENABLE = 0x17,		
	/* Light 0 enable */
	LIGHT_ENABLE0 = 0x18,		
	/* Light 1 enable */
	LIGHT_ENABLE1 = 0x19,		
	/* Light 2 enable */
	LIGHT_ENABLE2 = 0x1a,		
	/* Light 3 enable */
	LIGHT_ENABLE3 = 0x1b,		
	/* Clipping enable */
	DEPTH_CLIP_ENABLE = 0x1c,	
	/* Culling enable */
	CULL_FACE_ENABLE = 0x1d,	
	/* Texture mapping enable */
	TEXTURE_ENABLE = 0x1e,		
	/* Fog enable */
	FOG_ENABLE = 0x1f,			
	/* Dithering enable */
	DITHER_ENABLE = 0x20,		
	/* Alpha blending enable */
	ALPHA_BLEND_ENABLE = 0x21,	
	/* Alpha testing enable */
	ALPHA_TEST_ENABLE = 0x22,	
	/* Z testing enable */
	Z_TEST_ENABLE = 0x23,		
	/* Stencil testing enable */
	STENCIL_TEST_ENABLE = 0x24, 
	/* Anti-aliasing enable */
	ANTI_ALIAS_ENABLE = 0x25,	
	/* Patch culling enable */
	PATCH_CULL_ENABLE = 0x26,	
	/* Color testing enable */
	COLOR_TEST_ENABLE = 0x27,	
	/* Logical operation enable */
	LOGIC_OP_ENABLE = 0x28,		

	/* Bone matrix number */
	BONE_MATRIX_NUMBER = 0x2a, 
	/* Bone matrix data */
	BONE_MATRIX_DATA = 0x2b,   
	/* Morph weight 0 */
	MORPH_WEIGHT0 = 0x2c,	   
	/* Morph weight 1 */
	MORPH_WEIGHT1 = 0x2d,	   
	/* Morph weight 2 */
	MORPH_WEIGHT2 = 0x2e,	   
	/* Morph weight 3 */
	MORPH_WEIGHT3 = 0x2f,	   
	/* Morph weight 4 */
	MORPH_WEIGHT4 = 0x30,	   
	/* Morph weight 5 */
	MORPH_WEIGHT5 = 0x31,	   
	/* Morph weight 6 */
	MORPH_WEIGHT6 = 0x32,	   
	/* Morph weight 7 */
	MORPH_WEIGHT7 = 0x33,	   

	/* Patch division count */
	PATCH_DIVISION = 0x36,		
	/* Patch primitive type */
	PATCH_PRIMITIVE = 0x37,		
	/* Patch facing */
	PATCH_FACING = 0x38,		
	/* World matrix number */
	WORLD_MATRIX_NUMBER = 0x3a, 
	/* World matrix data */
	WORLD_MATRIX_DATA = 0x3b,	
	/* View matrix number */
	VIEW_MATRIX_NUMBER = 0x3c,	
	/* View matrix data */
	VIEW_MATRIX_DATA = 0x3d,	
	/* Projection matrix number */
	PROJ_MATRIX_NUMBER = 0x3e,	
	/* Projection matrix data */
	PROJ_MATRIX_DATA = 0x3f,	
	/* Texture generation matrix number */
	TGEN_MATRIX_NUMBER = 0x40,	
	/* Texture generation matrix data */
	TGEN_MATRIX_DATA = 0x41,	

	/* Viewport X scale */
	VIEWPORT_X_SCALE = 0x42,  
	/* Viewport Y scale */
	VIEWPORT_Y_SCALE = 0x43,  
	/* Viewport Z scale */
	VIEWPORT_Z_SCALE = 0x44,  
	/* Viewport X center */
	VIEWPORT_X_CENTER = 0x45, 
	/* Viewport Y center */
	VIEWPORT_Y_CENTER = 0x46, 
	/* Viewport Z center */
	VIEWPORT_Z_CENTER = 0x47, 
	/* Texture scale U */
	TEX_SCALE_U = 0x48,		  
	/* Texture scale V */
	TEX_SCALE_V = 0x49,		  
	/* Texture offset U */
	TEX_OFFSET_U = 0x4a,	  
	/* Texture offset V */
	TEX_OFFSET_V = 0x4b,	  
	/* Screen Offset X */
	OFFSET_X = 0x4c,		  
	/* Screen Offset Y */
	OFFSET_Y = 0x4d,		  

	/* Shade mode */
	SHADE_MODE = 0x50,			   
	/* Normal reverse */
	NORMAL_REVERSE = 0x51,		   
	/* Material color */
	MATERIAL_COLOR = 0x53,		   
	/* Material emissive */
	MATERIAL_EMISSIVE = 0x54,	   
	/* Ambient color */
	AMBIENT_COLOR = 0x55,		   
	/* Material diffuse */
	MATERIAL_DIFFUSE = 0x56,	   
	/* Material specular */
	MATERIAL_SPECULAR = 0x57,	   
	/* Ambient alpha */
	AMBIENT_ALPHA = 0x58,		   
	/* Material specular coefficient */
	MATERIAL_SPECULAR_COEF = 0x5b, 
	/* Ambient light color */
	AMBIENT_LIGHT_COLOR = 0x5c,	   
	/* Ambient light alpha */
	AMBIENT_LIGHT_ALPHA = 0x5d,	   
	/* Light mode */
	LIGHT_MODE = 0x5e,			   

	/* Light type 0 */
	LIGHT_TYPE0 = 0x5f, 
	/* Light type 1 */
	LIGHT_TYPE1 = 0x60, 
	/* Light type 2 */
	LIGHT_TYPE2 = 0x61, 
	/* Light type 3 */
	LIGHT_TYPE3 = 0x62, 
	/* Light 0 X */
	LIGHT0_X = 0x63,	
	/* Light 0 Y */
	LIGHT0_Y = 0x64,	
	/* Light 0 Z */
	LIGHT0_Z = 0x65,	
	/* Light 1 X */
	LIGHT1_X = 0x66,	
	/* Light 1 Y */
	LIGHT1_Y = 0x67,	
	/* Light 1 Z */
	LIGHT1_Z = 0x68,	
	/* Light 2 X */
	LIGHT2_X = 0x69,	
	/* Light 2 Y */
	LIGHT2_Y = 0x6a,	
	/* Light 2 Z */
	LIGHT2_Z = 0x6b,	
	/* Light 3 X */
	LIGHT3_X = 0x6c,	
	/* Light 3 Y */
	LIGHT3_Y = 0x6d,	
	/* Light 3 Z */
	LIGHT3_Z = 0x6e,	

	/* Light 0 direction X */
	LIGHT0_DIRECTION_X = 0x6f, 
	/* Light 0 direction Y */
	LIGHT0_DIRECTION_Y = 0x70, 
	/* Light 0 direction Z */
	LIGHT0_DIRECTION_Z = 0x71, 
	/* Light 1 direction X */
	LIGHT1_DIRECTION_X = 0x72, 
	/* Light 1 direction Y */
	LIGHT1_DIRECTION_Y = 0x73, 
	/* Light 1 direction Z */
	LIGHT1_DIRECTION_Z = 0x74, 
	/* Light 2 direction X */
	LIGHT2_DIRECTION_X = 0x75, 
	/* Light 2 direction Y */
	LIGHT2_DIRECTION_Y = 0x76, 
	/* Light 2 direction Z */
	LIGHT2_DIRECTION_Z = 0x77, 
	/* Light 3 direction X */
	LIGHT3_DIRECTION_X = 0x78, 
	/* Light 3 direction Y */
	LIGHT3_DIRECTION_Y = 0x79, 
	/* Light 3 direction Z */
	LIGHT3_DIRECTION_Z = 0x7a, 

	/* Light 0 constant attenuation */
	LIGHT0_CONSTANT_ATTEN = 0x7b,  
	/* Light 0 linear attenuation */
	LIGHT0_LINEAR_ATTEN = 0x7c,	   
	/* Light 0 quadratic attenuation */
	LIGHT0_QUADRATIC_ATTEN = 0x7d, 
	/* Light 1 constant attenuation */
	LIGHT1_CONSTANT_ATTEN = 0x7e,  
	/* Light 1 linear attenuation */
	LIGHT1_LINEAR_ATTEN = 0x7f,	   
	/* Light 1 quadratic attenuation */
	LIGHT1_QUADRATIC_ATTEN = 0x80, 
	/* Light 2 constant attenuation */
	LIGHT2_CONSTANT_ATTEN = 0x81,  
	/* Light 2 linear attenuation */
	LIGHT2_LINEAR_ATTEN = 0x82,	   
	/* Light 2 quadratic attenuation */
	LIGHT2_QUADRATIC_ATTEN = 0x83, 
	/* Light 3 constant attenuation */
	LIGHT3_CONSTANT_ATTEN = 0x84,  
	/* Light 3 linear attenuation */
	LIGHT3_LINEAR_ATTEN = 0x85,	   
	/* Light 3 quadratic attenuation */
	LIGHT3_QUADRATIC_ATTEN = 0x86, 

	/* Light 0 exponent attenuation */
	LIGHT0_EXPONENT_ATTEN = 0x87, 
	/* Light 1 exponent attenuation */
	LIGHT1_EXPONENT_ATTEN = 0x88, 
	/* Light 2 exponent attenuation */
	LIGHT2_EXPONENT_ATTEN = 0x89, 
	/* Light 3 exponent attenuation */
	LIGHT3_EXPONENT_ATTEN = 0x8a, 

	/* Light 0 cutoff attenuation */
	LIGHT0_CUTOFF_ATTEN = 0x8b, 
	/* Light 1 cutoff attenuation */
	LIGHT1_CUTOFF_ATTEN = 0x8c, 
	/* Light 2 cutoff attenuation */
	LIGHT2_CUTOFF_ATTEN = 0x8d, 
	/* Light 3 cutoff attenuation */
	LIGHT3_CUTOFF_ATTEN = 0x8e, 

	/* Light 0 ambient */
	LIGHT0_AMBIENT = 0x8f,	
	/* Light 0 diffuse */
	LIGHT0_DIFFUSE = 0x90,	
	/* Light 0 specular */
	LIGHT0_SPECULAR = 0x91, 
	/* Light 1 ambient */
	LIGHT1_AMBIENT = 0x92,	
	/* Light 1 diffuse */
	LIGHT1_DIFFUSE = 0x93,	
	/* Light 1 specular */
	LIGHT1_SPECULAR = 0x94, 
	/* Light 2 ambient */
	LIGHT2_AMBIENT = 0x95,	
	/* Light 2 diffuse */
	LIGHT2_DIFFUSE = 0x96,	
	/* Light 2 specular */
	LIGHT2_SPECULAR = 0x97, 
	/* Light 3 ambient */
	LIGHT3_AMBIENT = 0x98,	
	/* Light 3 diffuse */
	LIGHT3_DIFFUSE = 0x99,	
	/* Light 3 specular */
	LIGHT3_SPECULAR = 0x9a, 

	/* Culling */
	CULL = 0x9b, 

	/* Frame buffer pointer */
	FRAME_BUF_PTR = 0x9c,	
	/* Frame buffer width */
	FRAME_BUF_WIDTH = 0x9d, 
	/* Z buffer pointer */
	Z_BUF_PTR = 0x9e,		
	/* Z buffer width */
	Z_BUF_WIDTH = 0x9f,		

	/* Texture address 0 */
	TEX_ADDR0 = 0xa0,	   
	/* Texture address 1 */
	TEX_ADDR1 = 0xa1,	   
	/* Texture address 2 */
	TEX_ADDR2 = 0xa2,	   
	/* Texture address 3 */
	TEX_ADDR3 = 0xa3,	   
	/* Texture address 4 */
	TEX_ADDR4 = 0xa4,	   
	/* Texture address 5 */
	TEX_ADDR5 = 0xa5,	   
	/* Texture address 6 */
	TEX_ADDR6 = 0xa6,	   
	/* Texture address 7 */
	TEX_ADDR7 = 0xa7,	   
	/* Texture buffer width 0 */
	TEX_BUF_WIDTH0 = 0xa8, 
	/* Texture buffer width 1 */
	TEX_BUF_WIDTH1 = 0xa9, 
	/* Texture buffer width 2 */
	TEX_BUF_WIDTH2 = 0xaa, 
	/* Texture buffer width 3 */
	TEX_BUF_WIDTH3 = 0xab, 
	/* Texture buffer width 4 */
	TEX_BUF_WIDTH4 = 0xac, 
	/* Texture buffer width 5 */
	TEX_BUF_WIDTH5 = 0xad, 
	/* Texture buffer width 6 */
	TEX_BUF_WIDTH6 = 0xae, 
	/* Texture buffer width 7 */
	TEX_BUF_WIDTH7 = 0xaf, 

	/* CLUT buffer pointer */
	CLUT_BUF_PTR = 0xb0,
	/* CLUT buffer width */
	CLUT_BUF_WIDTH = 0xb1, 

	/* Transfer source */
	TRANSFER_SRC = 0xb2,   
	/* Transfer source width */
	TRANSFER_SRC_W = 0xb3, 
	/* Transfer destination */
	TRANSFER_DST = 0xb4,   
	/* Transfer destination width */
	TRANSFER_DST_W = 0xb5, 

	/* Texture size 0 */
	TEX_SIZE0 = 0xb8, 
	/* Texture size 1 */
	TEX_SIZE1 = 0xb9, 
	/* Texture size 2 */
	TEX_SIZE2 = 0xba, 
	/* Texture size 3 */
	TEX_SIZE3 = 0xbb, 
	/* Texture size 4 */
	TEX_SIZE4 = 0xbc, 
	/* Texture size 5 */
	TEX_SIZE5 = 0xbd, 
	/* Texture size 6 */
	TEX_SIZE6 = 0xbe, 
	/* Texture size 7 */
	TEX_SIZE7 = 0xbf, 

	/* Texture map mode */
	TEX_MAP_MODE = 0xc0,	  
	/* Texture shade mapping */
	TEX_SHADE_MAPPING = 0xc1, 
	/* Texture mode */
	TEX_MODE = 0xc2,		  
	/* Texture format */
	TEX_FORMAT = 0xc3,		  
	/* Load CLUT */
	CLUT_LOAD = 0xc4,		  
	/* CLUT format */
	CLUT_FORMAT = 0xc5,		  
	/* Texture filter */
	TEX_FILTER = 0xc6,		  
	/* Texture wrap */
	TEX_WRAP = 0xc7,		  
	/* Texture level */
	TEX_LEVEL = 0xc8,		  
	/* Texture function */
	TEX_FUNC = 0xc9,		  
	/* Texture environment color */
	TEX_ENV_COLOR = 0xca,	  
	/* Texture flush */
	TEX_FLUSH = 0xcb,		  
	/* Texture sync */
	TEX_SYNC = 0xcc,		  

	/* Fog 1 */
	FOG1 = 0xcd,		  
	/* Fog 2 */
	FOG2 = 0xce,		  
	/* Fog color */
	FOG_COLOR = 0xcf,	  
	/* Texture LOD slope */
	TEX_LOD_SLOPE = 0xd0, 

	/* Frame buffer pixel format */
	FRAMEBUF_PIX_FORMAT = 0xd2, 
	/* Clear mode */
	CLEAR_MODE = 0xd3,			
	/* Scissor 1 */
	SCISSOR1 = 0xd4,			
	/* Scissor 2 */
	SCISSOR2 = 0xd5,			

	/* Minimum Z */
	MIN_Z = 0xd6,		   
	/* Maximum Z */
	MAX_Z = 0xd7,		   
	/* Color test */
	COLOR_TEST = 0xd8,	   
	/* Color reference */
	COLOR_REF = 0xd9,	   
	/* Color test mask */
	COLOR_TESTMASK = 0xda, 
	/* Alpha test */
	ALPHA_TEST = 0xdb,	   
	/* Stencil test */
	STENCIL_TEST = 0xdc,   
	/* Stencil operation */
	STENCIL_OP = 0xdd,	   
	/* Z test */
	Z_TEST = 0xde,		   
	/* Blend mode */
	BLEND_MODE = 0xdf,	   
	/* Blend fixed A */
	BLEND_FIXED_A = 0xe0,  
	/* Blend fixed B */
	BLEND_FIXED_B = 0xe1,  
	/* Dither 0 */
	DITH0 = 0xe2,		   
	/* Dither 1 */
	DITH1 = 0xe3,		   
	/* Dither 2 */
	DITH2 = 0xe4,		   
	/* Dither 3 */
	DITH3 = 0xe5,		   

	/* Logical operation */
	LOGIC_OP = 0xe6,   
	/* Z mask */
	Z_MASK = 0xe7,	   
	/* Mask color */
	MASK_COLOR = 0xe8, 
	/* Mask alpha */
	MASK_ALPHA = 0xe9, 

	/* Transfer start */
	TRANSFER_START = 0xea,		
	/* Transfer source offset */
	TRANSFER_SRC_OFFSET = 0xeb, 
	/* Transfer destination offset */
	TRANSFER_DST_OFFSET = 0xec, 
	/* Transfer format */
	TRANSFER_FORMAT = 0xed,		
	/* Transfer size */
	TRANSFER_SIZE = 0xee,		

	/* Transfer flip */
	TRANSFER_FLIP = 0xef,				   
	/* Transfer out size */
	TRANSFER_OUT_SIZE = 0xf0,			   
	/* Transfer out format */
	TRANSFER_OUT_FORMAT = 0xf1,			   
	/* Vertex weight */
	VERTEX_WEIGHT = 0xf2,				   
	/* Vertex weight address */
	VERTEX_WEIGHT_ADDR = 0xf3,			   
	/* Vertex weight size */
	VERTEX_WEIGHT_SIZE = 0xf4,			   
	/* Vertex weight type */
	VERTEX_WEIGHT_TYPE = 0xf5,			   
	/* Vertex weight model */
	VERTEX_WEIGHT_MODEL = 0xf6,			   
	/* Vertex weight normalize */
	VERTEX_WEIGHT_NORMALIZE = 0xf7,		   
	/* Vertex weight offset */
	VERTEX_WEIGHT_OFFSET = 0xf8,		   
	/* Vertex weight scale */
	VERTEX_WEIGHT_SCALE = 0xf9,			   
	/* Vertex weight matrix */
	VERTEX_WEIGHT_MATRIX = 0xfa,		   
	/* Vertex weight matrix address */
	VERTEX_WEIGHT_MATRIX_ADDR = 0xfb,	   
	/* Vertex weight matrix size */
	VERTEX_WEIGHT_MATRIX_SIZE = 0xfc,	   
	/* Vertex weight matrix type */
	VERTEX_WEIGHT_MATRIX_TYPE = 0xfd,	   
	/* Vertex weight matrix model */
	VERTEX_WEIGHT_MATRIX_MODEL = 0xfe,	   
	/* Vertex weight matrix normalize */
	VERTEX_WEIGHT_MATRIX_NORMALIZE = 0xff, 
} GECommand;


typedef struct SceGupList {
		unsigned int *start;
		unsigned int *current;
		unsigned int size;
} SceGupList;

typedef struct SceGupBBox {
		int nest;
		unsigned int *pBjump[32];
} SceGupBBox;

typedef struct SceGupState {
	unsigned int size;

	unsigned int features;

	struct {
		int fpf;
		int width;
		int height;
	} fbuf;

	struct {
		int	en;
		int	x1;
		int	y1;
		int	x2;
		int	y2;
	} scissor;

	struct {
		int sw;
		int	sh;
		int	dw;
		int	dh;
	} sprite;

	struct {
		unsigned int color;
		int stencil;
		int	depth;
	} clear;

	struct {
		int	znear;
		int	zfar;
		int	offset;
	} depth;

	struct {
		int	tfunc_cd;
		int	tfunc_txf;
		int	tfunc_tcc;
		int	tmi;
		int	tmn;
	} texture;
} SceGupState;

typedef struct SceGupContext {
	unsigned int size;

	SceGupList list;
	SceGupBBox bbox;
	SceGupState state;

} SceGupContext;

/** @addtogroup GUP */
/**@{*/

static inline int getExp(int val)
{
	return 31 - __builtin_clz(val & 0x3FF);
}

/*E Get bounding box nest level                */
static inline int sceGupGetBoundingBoxNest(SceGupContext *context)
{
	return (context->bbox.nest);
}

/**
  * Send raw command to the GE
  *
  * Only the 24 lower bits of the argument is passed along.
  *
  * @param list - Pointer to the GUP list
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
static inline void sceGupSendCommandi(SceGupContext *context, GECommand cmd, unsigned int argument) {
  *context->list.current++ = (cmd << 24) | (argument & 0xffffff);
}

/**
  * Send raw float-command to the GE
  *
  * The argument is converted into a 24-bit float before transfer.
  *
  * @param list - Pointer to the GUP list
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
static inline void sceGupSendCommandf(SceGupContext *context, GECommand cmd, float argument)
{
	union
	{
		float f;
		unsigned int i;
	} t;
	t.f = argument;

	sceGupSendCommandi(context, cmd, t.i >> 8);
}

/**
  * Set texture map mode
  *
  * @param context - Pointer to the GUP context
  * @param tmn - Texture map mode
  * @param tmi - Texture map index
**/
static inline void sceGupPutTexMap(SceGupContext *context, int tmn, int tmi)
{
	sceGupSendCommandi(context, TEX_MAP_MODE, (tmn << 8) | tmi);
}

/**
  * Set texture shade map mode
  *
  * @param context - Pointer to the GUP context
  * @param lu - Texture shade map mode
  * @param lv - Texture shade map index
**/
static inline void sceGupPutTexShade(SceGupContext *context, int lu, int lv)
{
	sceGupSendCommandi(context, TEX_SHADE_MAPPING, (lu << 8) | lv);
}

/**
  * Flush texture page-cache
  *
  * Do this if you have copied/rendered into an area currently in the texture-cache
  *
  * @param context - Pointer to the GUP context
**/
static inline void sceGupTexFlush(SceGupContext *context) {
  sceGupSendCommandi(context, TEX_FLUSH, 0);
}

/*E Set texture mode       */
static inline void sceGupPutTexMode(SceGupContext *context, int tpf, int ext, int maxlod, int mc, int hsm)
{
	sceGupSendCommandi(context, TEX_MODE, (hsm << 16) | (mc << 8) | maxlod);
	sceGupSendCommandi(context, TEX_FILTER, (tpf << 8) | ext);
	sceGupTexFlush(context);
}

/**
  * Set depth buffer parameters
  *
  * @param context - Pointer to the GUP context
  * @param zbp - VRAM pointer where the depthbuffer should start
  * @param zbw - The width of the depth-buffer (block-aligned)
  *
**/
static inline void sceGupDepthBuffer(SceGupContext *context, void* zbp, int zbw) {
  sceGupSendCommandi(context, Z_BUF_PTR, ((unsigned int)zbp));
	sceGupSendCommandi(context, Z_BUF_WIDTH, ((((unsigned int)zbp) & 0xff000000) >> 8) | zbw);
}

/**
  * Set draw buffer parameters (and store in context for buffer-swap)
  *
  * Available pixel formats are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @par Example: Setup a standard 16-bit draw buffer
  * @code
  * sceGupDrawBuffer(context,GU_PSM_5551,(void*)0,512);
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param psm - Pixel format to use for rendering (and display)
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
static inline void sceGupDrawBuffer(SceGupContext *context, int psm, void* fbp, int fbw) {
  sceGupSendCommandi(context, FRAMEBUF_PIX_FORMAT, psm);
  sceGupSendCommandi(context, FRAME_BUF_PTR, (unsigned int)fbp);
	sceGupSendCommandi(context, FRAME_BUF_WIDTH, ((((unsigned int)fbp) & 0xff000000) >> 8) | fbw);
}

/**
  * Select which depth-test function to use
  *
  * Valid choices for the depth-test are:
  *   - GU_NEVER - No pixels pass the depth-test
  *   - GU_ALWAYS - All pixels pass the depth-test
  *   - GU_EQUAL - Pixels that match the depth-test pass
  *   - GU_NOTEQUAL - Pixels that doesn't match the depth-test pass
  *   - GU_LESS - Pixels that are less in depth passes
  *   - GU_LEQUAL - Pixels that are less or equal in depth passes
  *   - GU_GREATER - Pixels that are greater in depth passes
  *   - GU_GEQUAL - Pixels that are greater or equal passes
  *
  * @param context - Pointer to the GUP context
  * @param function - Depth test function to use
**/
static inline void sceGupDepthFunc(SceGupContext *context, int function) {
  sceGupSendCommandi(context, Z_TEST, function);
}

/**
  * Mask depth buffer writes
  *
  * @param context - Pointer to the GUP context
  * @param mask - GU_TRUE(1) to disable Z writes, GU_FALSE(0) to enable
**/
static inline void sceGupDepthMask(SceGupContext *context, int mask) {
  sceGupSendCommandi(context, Z_MASK, mask);
}

/**
  * Set depth offset
  *
  * @param context - Pointer to the GUP context
  * @param offset - Depth offset to use
**/
static inline void sceGupPutDepthRangeWithOffset(SceGupContext *context, int znear, int zfar, int offset) {
  unsigned int max = (unsigned int)znear + (unsigned int)zfar;
  int val = (int)((max >> 31) + max);
  float z = (float)(val >> 1);

  if (znear > zfar)
  {
    int temp = znear;
    znear = zfar;
    zfar = temp;
  }

  sceGupSendCommandf(context, VIEWPORT_Z_SCALE, z - ((float)znear));
  sceGupSendCommandf(context, VIEWPORT_Z_CENTER, z + ((float)context->state.depth.offset));
  sceGupSendCommandi(context, MIN_Z, znear);
  sceGupSendCommandi(context, MAX_Z, zfar);
}

/**
  * Set which range to use for depth calculations.
  *
  * @note The depth buffer is inversed, and takes values from 65535 to 0.
  *
  * Example: Use the entire depth-range for calculations:
  * @code
  * sceGuDepthRange(65535,0);
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param near - Value to use for the near plane
  * @param far - Value to use for the far plane
**/
static inline void sceGupDepthRange(SceGupContext *context, int near, int far) {
  context->state.depth.znear = near;
	context->state.depth.zfar  = far;
  sceGupPutDepthRangeWithOffset(context, near, far, context->state.depth.offset);
}

/**
  * Set depth offset
  *
  * @param offset - Depth offset to use
**/
static inline void sceGupDepthOffset(SceGupContext *context, unsigned int offset) {
  context->state.depth.offset = offset;
  sceGupPutDepthRangeWithOffset(context, context->state.depth.znear, context->state.depth.zfar, offset);
}

/**
  * Trigger signal to call code from the command stream
  * 
  * Available signals are:
  *   - GU_SIGNAL_WAIT - Wait for callback to finish
  *   - GU_SIGNAL_NOWAIT - Do not wait for callback to finish
  *   - GU_SIGNAL_PAUSE - Pause execution until callback is finished
  *
  * Available behaviors are:
  *   - GU_BEHAVIOR_SUSPEND - Stops display list execution until callback function finished
  *   - GU_BEHAVIOR_CONTINUE - Do not stop display list execution during callback
  *
  * @param context - Pointer to the GUP context
  * @param signal - Signal to trigger
  * @param behavior - Behavior type
**/
static inline void sceGupSignal(SceGupContext *context, int signal, int behavior) {
  sceGupSendCommandi(context, SIGNAL, ((signal & 0xff) << 16) | (behavior & 0xffff));
	sceGupSendCommandi(context, END, 0);

	if (signal == GU_SIGNAL_PAUSE)
	{
		sceGupSendCommandi(context, FINISH, 0);
		sceGupSendCommandi(context, END, 0);
	}
}

/**
  * Get the start address of the list in the GUP context
  *
  * @param context - Pointer to the GUP context
  * @return The start address of the list in the GUP context
**/
static inline void *sceGupGetStartAddr(SceGupContext *context)
{
	return context->list.start;
}

/**
  * Get the current address of the list in the GUP context
  *
  * @param context - Pointer to the GUP context
  * @return The current address of the list in the GUP context
**/
static inline void *sceGupGetCurrentAddr(SceGupContext *context) {
  return context->list.current;
}

/**
  * Get the current address of the list in the GUP context
  *
  * @param context - Pointer to the GUP context
  * @return The current address of the list in the GUP context
**/
static inline void sceGupSetCurrentAddr(SceGupContext *context, void *addr) {
  context->list.current = addr;
}

/**
  * Allocate memory on the current display list for temporary storage
  *
  * @note This function is NOT for permanent memory allocation, the
  * memory will be invalid as soon as you start filling the same display
  * list again.
  *
  * @param context - Pointer to the GUP context
  * @param size - How much memory to allocate
  * @return Memory-block ready for use
**/
static inline void *sceGupGetMemory(SceGupContext *context, unsigned int size) {
  unsigned int *dst;
  unsigned int *current = sceGupGetCurrentAddr(context);

  dst = current + ((size + 3) / 4) + 2;

  sceGupSendCommandi(context, BASE, ((((unsigned int)dst) >> 8) & 0xf0000));
  sceGupSendCommandi(context, JUMP, (unsigned int)dst);

  sceGupSetCurrentAddr(context, dst);

  return (void *)dst + 2;
}

/**
  * Start filling a new display-context
  *
  * Contexts available are:
  *   - GU_DIRECT - Rendering is performed as list is filled
  *   - GU_CALL - List is setup to be called from the main list
  *   - GU_SEND - List is buffered for a later call to sceGuSendList()
  *
  * The previous context-type is stored so that it can be restored at sceGuFinish().
  *
  * @param context - Pointer to the GUP context
  * @param list - Pointer to display-list (16 byte aligned)
  * @param size - Size of the display-list
**/
static inline void sceGupStart(SceGupContext *context, void *list, int size) {
  context->list.start = (unsigned int *)list;
  context->list.current = context->list.start;
  context->list.size = size;
}

/**
  * Reset state
  *
  * @param state - Pointer to the GUP state
**/
static inline void sceGupResetState(SceGupState *state)
{
	state->size        = sizeof(SceGupState);
	state->features    = 0;

	/* frame buffer */
	state->fbuf.fpf    = GU_PSM_5551;
	state->fbuf.width  = GU_SCR_WIDTH;
	state->fbuf.height = GU_SCR_HEIGHT;

	/* scissoring */
	state->scissor.en = 0;
	state->scissor.x1 = 0;
	state->scissor.y1 = 0;
	state->scissor.x2 = 0;
	state->scissor.y2 = 0;

	/* depth range */
	state->depth.znear  = 0;
	state->depth.zfar   = 1;
	state->depth.offset = 0;

	/* sprite parameter */
	state->sprite.sw = 0;
	state->sprite.sh = 0;
	state->sprite.dw = 0;
	state->sprite.dh = 0;

	/* clear parameter */
	state->clear.color   = 0x00000000;
	state->clear.stencil = 0x0;
	state->clear.depth   = 0xFFFF;

	/* tex parameters */
	state->texture.tfunc_cd  = 0;
	state->texture.tfunc_tcc = 0;
	state->texture.tfunc_txf = 0;
	state->texture.tmi = 0;
	state->texture.tmn = 0;
}

/**
  * Reset bounding box
  *
  * @param bbox - Pointer to the GUP bounding box
**/
static inline void sceGupResetBBox(SceGupBBox *bbox)
{
	bbox->nest = 0;
}

/**
  * Initialize context
  *
  * @param context - Pointer to the GUP context
**/
static inline void sceGupResetContext(SceGupContext *context)
{
	unsigned int i;
	unsigned int *p;
 
  p = (unsigned int *)context;

	for (i=0; i<(sizeof(context) / 4); i++) {
		*p++ = 0x00;
	}

	context->size = sizeof(context);

	sceGupResetBBox(&context->bbox);
	sceGupResetState(&context->state);
}

/**
  * Finish current display list and go back to the parent context, sending argument id for
  * the finish callback.
  *
  * If the context is GU_DIRECT, the stall-address is updated so that the entire list will
  * execute. Otherwise, only the terminating action is written to the list, depending on
  * context-type.
  *
  * @param context - Pointer to the GUP context
  * @param id - Finish callback id (16-bit)
**/
static inline void sceGupFinishId(SceGupContext *context, unsigned int id) {
  sceGupSendCommandi(context, FINISH, id & 0xffff);
	sceGupSendCommandi(context, END, 0);
}

/**
  * Draw array of vertices forming primitives
  *
  * Available primitive-types are:
  *   - GU_POINTS - Single pixel points (1 vertex per primitive)
  *   - GU_LINES - Single pixel lines (2 vertices per primitive)
  *   - GU_LINE_STRIP - Single pixel line-strip (2 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLES - Filled triangles (3 vertices per primitive)
  *   - GU_TRIANGLE_STRIP - Filled triangles-strip (3 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLE_FAN - Filled triangle-fan (3 vertices for the first primitive, 1 for every following)
  *   - GU_SPRITES - Filled blocks (2 vertices per primitive)
  *
  * The vertex-type decides how the vertices align and what kind of information they contain.\n
  * The following flags are ORed together to compose the final vertex format:
  *   - GU_TEXTURE_8BIT - 8-bit texture coordinates
  *   - GU_TEXTURE_16BIT - 16-bit texture coordinates
  *   - GU_TEXTURE_32BITF - 32-bit texture coordinates (float)
  *
  *   - GU_COLOR_5650 - 16-bit color (R5G6B5A0)
  *   - GU_COLOR_5551 - 16-bit color (R5G5B5A1)
  *   - GU_COLOR_4444 - 16-bit color (R4G4B4A4)
  *   - GU_COLOR_8888 - 32-bit color (R8G8B8A8)
  *
  *   - GU_NORMAL_8BIT - 8-bit normals
  *   - GU_NORMAL_16BIT - 16-bit normals
  *   - GU_NORMAL_32BITF - 32-bit normals (float)
  *
  *   - GU_VERTEX_8BIT - 8-bit vertex position
  *   - GU_VERTEX_16BIT - 16-bit vertex position
  *   - GU_VERTEX_32BITF - 32-bit vertex position (float)
  *
  *   - GU_WEIGHT_8BIT - 8-bit weights
  *   - GU_WEIGHT_16BIT - 16-bit weights
  *   - GU_WEIGHT_32BITF - 32-bit weights (float)
  *
  *   - GU_INDEX_8BIT - 8-bit vertex index
  *   - GU_INDEX_16BIT - 16-bit vertex index
  *
  *   - GU_WEIGHTS(n) - Number of weights (1-8)
  *   - GU_VERTICES(n) - Number of vertices (1-8)
  *
  *   - GU_TRANSFORM_2D - Coordinate is passed directly to the rasterizer
  *   - GU_TRANSFORM_3D - Coordinate is transformed before passed to rasterizer
  *
  * Data members inside a vertex are laid out in the following order:
  * - Weights - if GU_WEIGHTS(n) is used N weights are present
  * - Texture Coordinates
  * - Color
  * - Normal
  * - Position
  *
  * If GU_VERTICES(n) is used the entire vertex structure is repeated N-times.\n
  * A member is only present if related type flag has been used (look at examples below).
  *
  * @note Every member making up a vertex must be aligned to 16 bits.
  *
  * @par Notes on 16 bit vertex/texture/normal formats:
  *   - Values are stored as 16-bit signed integers, with a range of -32768 to 32767
  *   - In the floating point coordinate space this is mapped as -1.0 to 1.0
  *   - To scale this to be such that the value 1 in 16 bit space is 1 unit in floating point space, use sceGumScale() for vertices; (see pspgum.h)
  *      - You can technically use this to create whatever fixed-point space you want (a common one is 5 bits for the decimals)
  *      - Caveat: you need to use the sceGumDrawArray method to apply the affine transform to the vertices.
  *      - sceGuDrawArray() will not apply the affine transform to the vertices.
  *   - To scale this for texture coordinates use sceGuTexOffset() and sceGuTexScale() (see below)
  *   - You can't scale the normals with any functions, which is expected since normals by definition are unit vectors.
  *
  * @code
  * sceGumScale(32768.0f, 32768.0f, 32768.0f); // This is an identity mapping -- 1 unit in floating point space is 1 unit in 16-bit space
  * sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|GU_VERTEX_16BIT, 3, 0, vertices);
  * @endcode
  *
  * @par Notes on 8 bit vertex/texture/normal formats:
  *   - Values are stored as 8-bit signed integers with a range of -128 to 127
  *   - In the floating point coordinate space this is mapped as -1.0 to 1.0
  *   - To scale this to be such that the value 1 in 8 bit space is 1 unit in floating point space, use sceGumScale() for vertices; (see above).
  *   - The scaling factor as demonstrated will be 128.0f.
  *   - See above for notes on texture and normals.
  *
  * @par Example: Render 400 triangles, with floating-point texture coordinates, and floating-point position, no indices
  * @code
  * sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,400*3,0,vertices);
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param prim - What kind of primitives to render
  * @param vtype - Vertex type to process
  * @param count - How many vertices to process
  * @param indices - Optional pointer to an index-list
  * @param vertices - Pointer to a vertex-list
**/
static inline void sceGupDrawArray(SceGupContext *context, int prim, int vtype, int count, const void* indices, const void* vertices) {
  if (vtype)
    sceGupSendCommandi(context, VERTEX_TYPE, vtype);

  if (indices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, IADDR, ((unsigned int)indices));
  }

  if (vertices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, VADDR, ((unsigned int)vertices));
  }

  sceGupSendCommandi(context, PRIM, (prim << 16) | count);
}

/**
  * Begin conditional rendering of object
  *
  * If no vertices passed into this function are inside the scissor region, it will skip rendering
  * the object. There can be up to 32 levels of conditional testing, and all levels HAVE to
  * be terminated by sceGuEndObject().
  *
  * @par Example: test a boundingbox against the frustum, and if visible, render object
  * @code
  * sceGuBeginObject(GU_VERTEX_32BITF,8,0,boundingBox);
  *   sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,vertexCount,0,vertices);
  * sceGuEndObject();
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param vtype - Vertex type to process
  * @param count - Number of vertices to test
  * @param indices - Optional list to an index-list
  * @param vertices - Pointer to a vertex-list
**/
static inline void sceGupBeginObject(SceGupContext *context, int vtype, int count, const void* indices, const void* vertices) {
  if (vtype)
		sceGupSendCommandi(context, VERTEX_TYPE, vtype);

	if (indices)
	{
		sceGupSendCommandi(context, BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sceGupSendCommandi(context, IADDR, ((unsigned int)indices));
	}

	if (vertices)
	{
		sceGupSendCommandi(context, BASE, (((unsigned int)vertices) >> 8) & 0x0f0000);
		sceGupSendCommandi(context, VADDR, ((unsigned int)vertices));
	}

	sceGupSendCommandi(context, BOUNDING_BOX, count);

	// store start to new object
  context->bbox.pBjump[context->bbox.nest++] = (unsigned int *)sceGupGetCurrentAddr(context);

	// dummy commands, overwritten in sceGuEndObject()
	sceGupSendCommandi(context, BASE, 0);
	sceGupSendCommandi(context, BJUMP, 0);
}

/**
  * End conditional rendering of object
  * 
  * @param context - Pointer to the GUP context
**/
#define SCE_ERROR_NOT_FOUND				0x80000025
static inline int sceGupEndObject(SceGupContext *context) {
  unsigned int *bjump;
	unsigned int *current;
	int bbox;

	bbox = context->bbox.nest - 1;
	if (bbox < 0) {
		return (SCE_ERROR_NOT_FOUND);
	}
	context->bbox.nest = bbox;

	current = (unsigned int *)sceGupGetCurrentAddr(context);

  /* Restore the current address and set the bounding box jump address */
	bjump = context->bbox.pBjump[bbox];
	sceGupSetCurrentAddr(context, bjump);
	sceGupSendCommandi(context, BASE, (unsigned int)current);
	sceGupSendCommandi(context, BJUMP, (unsigned int)current);
	sceGupSetCurrentAddr(context, (void *)current);

	return bbox;
}

/**
  * Set light parameters
  *
  * Available light types are:
  *   - GU_DIRECTIONAL - Directional light
  *   - GU_POINTLIGHT - Single point of light
  *   - GU_SPOTLIGHT - Point-light with a cone
  *
  * Available light components are:
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *   - GU_POWERED_DIFFUSE
  *
  * @param context - Pointer to the GUP context
  * @param light - Light index
  * @param type - Light type
  * @param components - Light components
  * @param position - Light position
**/
#define GE_LTYPE_DIFFUSE						0
#define GE_LTYPE_DIFFUSE_AND_SPECULAR			1
#define GE_LTYPE_POWERED_DIFFUSE_AND_SPECULAR	2
static inline void sceGupLight(SceGupContext *context, int light, int type, int components, const ScePspFVector3* position) {
  int ltype;
  int offset = light * 3;

	if (components == GE_LTYPE_POWERED_DIFFUSE_AND_SPECULAR) {
		ltype = GE_LTYPE_POWERED_DIFFUSE_AND_SPECULAR;
	} else if (components == GE_LTYPE_DIFFUSE_AND_SPECULAR) {
		ltype = GE_LTYPE_DIFFUSE_AND_SPECULAR;
	} else {
		ltype = GE_LTYPE_DIFFUSE;
	}

  // Light position
	sceGupSendCommandf(context, LIGHT0_X + offset, position->x);
	sceGupSendCommandf(context, LIGHT0_Y + offset, position->y);
	sceGupSendCommandf(context, LIGHT0_Z + offset, position->z);
	// Light type and components
	sceGupSendCommandi(context, LIGHT_TYPE0 + light, ((type & GU_AMBIENT_AND_DIFFUSE) << 8) | ltype);
}

/**
  * Set light attenuation
  *
  * @param context - Pointer to the GUP context
  * @param light - Light index
  * @param atten0 - Constant attenuation factor
  * @param atten1 - Linear attenuation factor
  * @param atten2 - Quadratic attenuation factor
**/
static inline void sceGupLightAtt(SceGupContext *context, int light, float atten0, float atten1, float atten2) {
  int offset = light * 3;
	sceGupSendCommandf(context, LIGHT0_CONSTANT_ATTEN + offset, atten0);
	sceGupSendCommandf(context, LIGHT0_LINEAR_ATTEN + offset, atten1);
	sceGupSendCommandf(context, LIGHT0_QUADRATIC_ATTEN + offset, atten2);
}

/**
  * Set light color
  *
  * Available light components are:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *
  * @param context - Pointer to the GUP context
  * @param light - Light index
  * @param component - Which component to set
  * @param color - Which color to use
**/
static inline void sceGupLightColor(SceGupContext *context, int light, int component, unsigned int color) {
  int offset = light * 3;

	switch (component)
	{
		case GU_AMBIENT: 
			sceGupSendCommandi(context, LIGHT0_AMBIENT + offset, color); 
			break;
		case GU_DIFFUSE: 
			sceGupSendCommandi(context, LIGHT0_DIFFUSE + offset, color); 
			break;
		case GU_SPECULAR: 
			sceGupSendCommandi(context, LIGHT0_SPECULAR + offset, color); 
			break;
		case GU_AMBIENT_AND_DIFFUSE:
			sceGupSendCommandi(context, LIGHT0_AMBIENT + offset, color); 
			sceGupSendCommandi(context, LIGHT0_DIFFUSE + offset, color); 
			break;
		case GU_DIFFUSE_AND_SPECULAR:
			sceGupSendCommandi(context, LIGHT0_DIFFUSE + offset, color); 
			sceGupSendCommandi(context, LIGHT0_SPECULAR + offset, color); 
			break;
	}

}

/**
  * Set light mode
  *
  * Available light modes are:
  *   - GU_SINGLE_COLOR
  *   - GU_SEPARATE_SPECULAR_COLOR
  *
  * Separate specular colors are used to interpolate the specular component
  * independently, so that it can be added to the fragment after the texture color.
  *
  * @param context - Pointer to the GUP context
  * @param mode - Light mode to use
**/
static inline void sceGupLightMode(SceGupContext *context, int mode) {
  sceGupSendCommandi(context, LIGHT_MODE, mode);
}

/**
  * Set spotlight parameters
  *
  * @param context - Pointer to the GUP context
  * @param light - Light index
  * @param direction - Spotlight direction
  * @param exponent - Spotlight exponent
  * @param cutoff - Spotlight cutoff angle (in radians)
**/
static inline void sceGupLightSpot(SceGupContext *context, int light, const ScePspFVector3* direction, float exponent, float cutoff) {
  int offset = light * 3;
	sceGupSendCommandf(context, LIGHT0_EXPONENT_ATTEN + light, exponent);
	sceGupSendCommandf(context, LIGHT0_CUTOFF_ATTEN + light, cutoff);

	sceGupSendCommandf(context, LIGHT0_DIRECTION_X + offset, direction->x);
	sceGupSendCommandf(context, LIGHT0_DIRECTION_Y + offset, direction->y);
	sceGupSendCommandf(context, LIGHT0_DIRECTION_Z + offset, direction->z);
}

/**
  * Set the current clear-color
  *
  * @param context - Pointer to the GUP context
  * @param color - Color to clear with
**/
static inline void sceGupClearColor(SceGupContext *context, unsigned int color) {
  context->state.clear.color = color;
}

/**
  * Set the current clear-depth
  *
  * @param context - Pointer to the GUP context
  * @param depth - Set which depth to clear with (0x0000-0xffff)
**/
static inline void sceGupClearDepth(SceGupContext *context, unsigned int depth) {
  context->state.clear.depth = depth;
}

/**
  * Set the current stencil clear value
  *
  * @param context - Pointer to the GUP context
  * @param stencil - Set which stencil value to clear with (0-255)
**/
static inline void sceGupClearStencil(SceGupContext *context, unsigned int stencil) {
  context->state.clear.stencil = stencil; 
}

/**
  * Set mask for which bits of the pixels to write
  *
  * @param context - Pointer to the GUP context
  * @param mask - Which bits to filter against writes
**/
static inline void sceGupPixelMask(SceGupContext *context, unsigned int mask) {
  sceGupSendCommandi(context, MASK_COLOR, mask);
	sceGupSendCommandi(context, MASK_ALPHA, mask >> 24);
}

/**
  * Set the material properties
  *
  * @param context - Pointer to the GUP context
  * @param mode - Material mode
  * @param color - Material color
**/
static inline void sceGupMaterial(SceGupContext *context, int mode, int color) {
  if (mode & GU_AMBIENT) {
		sceGupSendCommandi(context, AMBIENT_COLOR, color);
		sceGupSendCommandi(context, AMBIENT_ALPHA, color >> 24);
	}

	if (mode & GU_DIFFUSE)
		sceGupSendCommandi(context, MATERIAL_DIFFUSE, color);

	if (mode & GU_SPECULAR)
		sceGupSendCommandi(context, MATERIAL_SPECULAR, color);
}

/**
  * Set current primitive color
  *
  * @param context - Pointer to the GUP context
  * @param color - Which color to use (overriden by vertex-colors)
**/
static inline void sceGupColor(SceGupContext *context, unsigned int color) {
  sceGupMaterial(context, GU_AMBIENT | GU_DIFFUSE | GU_SPECULAR, color);
}

/**
  * Set the color test function
  *
  * The color test is only performed while GU_COLOR_TEST is enabled.
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *
  * @par Example: Reject any pixel that does not have 0 as the blue channel
  * @code
  * sceGuColorFunc(GU_EQUAL,0,0xff0000);
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param func - Color test function
  * @param color - Color to test against
  * @param mask - Mask ANDed against both source and destination when testing
**/
static inline void sceGupColorFunc(SceGupContext *context, int func, unsigned int color, unsigned int mask) {
  sceGupSendCommandi(context, COLOR_TEST, func);
	sceGupSendCommandi(context, COLOR_REF, color);
	sceGupSendCommandi(context, COLOR_TESTMASK, mask);
}

/**
  * Set which color components that the material will receive
  *
  * The components are ORed together from the following values:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *
  * @param context - Pointer to the GUP context
  * @param components - Which components to receive
**/
static inline void sceGupColorMaterial(SceGupContext *context, int components) {
  sceGupSendCommandi(context, MATERIAL_COLOR, components);
}

/**
  * Set the alpha test parameters
  *
  * Available comparison functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param context - Pointer to the GUP context
  * @param func - Specifies the alpha comparison function.
  * @param value - Specifies the reference value that incoming alpha values are compared to.
  * @param mask - Specifies the mask that both values are ANDed with before comparison.
**/
static inline void sceGupAlphaFunc(SceGupContext *context, int func, int value, int mask) {
  int arg = func | ((value & 0xff) << 8) | ((mask & 0xff) << 16);
	sceGupSendCommandi(context, ALPHA_TEST, arg);
}

/**
  * Set the ambient light color
  *
  * @param context - Pointer to the GUP context
  * @param color - The light color to set
**/
static inline void sceGupAmbient(SceGupContext *context, unsigned int color) {
  sceGupSendCommandi(context, AMBIENT_LIGHT_COLOR, color);
	sceGupSendCommandi(context, AMBIENT_LIGHT_ALPHA, color >> 24);
}

/**
  * Set the ambient color
  *
  * @param context - Pointer to the GUP context
  * @param color - The color to set
**/
static inline void sceGupAmbientColor(SceGupContext *context, unsigned int color) {
  sceGupSendCommandi(context, AMBIENT_COLOR, color);
	sceGupSendCommandi(context, AMBIENT_ALPHA, color >> 24);
}

/**
  * Set the blending-mode
  *
  * Keys for the blending operations:
  *   - Cs - Source color
  *   - Cd - Destination color
  *   - Bs - Blend function for source fragment
  *   - Bd - Blend function for destination fragment
  *
  * Available blending-operations are:
  *   - GU_ADD - (Cs*Bs) + (Cd*Bd)
  *   - GU_SUBTRACT - (Cs*Bs) - (Cd*Bd)
  *   - GU_REVERSE_SUBTRACT - (Cd*Bd) - (Cs*Bs)
  *   - GU_MIN - Cs < Cd ? Cs : Cd
  *   - GU_MAX - Cs < Cd ? Cd : Cs
  *   - GU_ABS - |Cs-Cd|
  *
  * Available blending-functions are:
  *   - GU_SRC_COLOR
  *   - GU_ONE_MINUS_SRC_COLOR
  *   - GU_SRC_ALPHA
  *   - GU_ONE_MINUS_SRC_ALPHA
  *   - GU_DST_ALPHA
  *   - GU_ONE_MINUS_DST_ALPHA
  *   - GU_DST_COLOR
  *   - GU_ONE_MINUS_DST_COLOR
  *   - GU_FIX
  *
  * @param context - Pointer to the GUP context
  * @param op - Blending Operation
  * @param src - Blending function for source operand
  * @param dest - Blending function for dest operand
  * @param srcfix - Fix value for GU_FIX (source operand)
  * @param destfix - Fix value for GU_FIX (dest operand)
**/
static inline void sceGupBlendFunc(SceGupContext *context, int op, int src, int dest, unsigned int srcfix, unsigned int destfix) {
  sceGupSendCommandi(context, BLEND_MODE, src | (dest << 4) | (op << 8));
	sceGupSendCommandi(context, BLEND_FIXED_A, srcfix);
	sceGupSendCommandi(context, BLEND_FIXED_B, destfix);
}

/**
  * Set the model color
  *
  * @param context - Pointer to the GUP context
  * @param emissive - Emissive color
  * @param ambient - Ambient color
  * @param diffuse - Diffuse color
  * @param specular - Specular color
**/
static inline void sceGupModelColor(SceGupContext *context, unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular) {
  sceGupSendCommandi(context, MATERIAL_EMISSIVE, emissive);
	sceGupSendCommandi(context, MATERIAL_DIFFUSE, diffuse);
	sceGupSendCommandi(context, AMBIENT_COLOR, ambient);
	sceGupSendCommandi(context, MATERIAL_SPECULAR, specular);
}

/**
  * Set stencil function and reference value for stencil testing
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param context - Pointer to the GUP context
  * @param func - Test function
  * @param ref - The reference value for the stencil test
  * @param mask - Mask that is ANDed with both the reference value and stored stencil value when the test is done
**/
static inline void sceGupStencilFunc(SceGupContext *context, int func, int ref, int mask) {
  sceGupSendCommandi(context, STENCIL_TEST, func | ((ref & 0xff) << 8) | ((mask & 0xff) << 16));
}

/**
  * Set the stencil test actions
  *
  * Available actions are:
  *   - GU_KEEP - Keeps the current value
  *   - GU_ZERO - Sets the stencil buffer value to zero
  *   - GU_REPLACE - Sets the stencil buffer value to ref, as specified by sceGuStencilFunc()
  *   - GU_INCR - Increments the current stencil buffer value
  *   - GU_DECR - Decrease the current stencil buffer value
  *   - GU_INVERT - Bitwise invert the current stencil buffer value
  *
  * As stencil buffer shares memory with framebuffer alpha, resolution of the buffer
  * is directly in relation.
  *
  * @param context - Pointer to the GUP context
  * @param fail - The action to take when the stencil test fails
  * @param zfail - The action to take when stencil test passes, but the depth test fails
  * @param zpass - The action to take when both stencil test and depth test passes
**/
static inline void sceGupStencilOp(SceGupContext *context, int fail, int zfail, int zpass) {
  sceGupSendCommandi(context, STENCIL_OP, fail | (zfail << 8) | (zpass << 16));
}

/**
  * Set the specular power for the material
  *
  * @param context - Pointer to the GUP context
  * @param power - Specular power
**/
static inline void sceGupSpecular(SceGupContext *context, float power) {
  sceGupSendCommandf(context, MATERIAL_SPECULAR_COEF, power);
}

/**
  * Set the current face-order (for culling)
  *
  * This only has effect when culling is enabled (GU_CULL_FACE)
  *
  * Culling order can be:
  *   - GU_CW - Clockwise primitives are not culled
  *   - GU_CCW - Counter-clockwise are not culled
  *
  * @param context - Pointer to the GUP context
  * @param order - Which order to use
**/
static inline void sceGupFrontFace(SceGupContext *context, int order) {
  sceGupSendCommandi(context, CULL, order ? 0 : 1);
}

/**
  * Set color logical operation
  *
  * Available operations are:
  *   - GU_CLEAR
  *   - GU_AND
  *   - GU_AND_REVERSE
  *   - GU_COPY
  *   - GU_AND_INVERTED
  *   - GU_NOOP
  *   - GU_XOR
  *   - GU_OR
  *   - GU_NOR
  *   - GU_EQUIV
  *   - GU_INVERTED
  *   - GU_OR_REVERSE
  *   - GU_COPY_INVERTED
  *   - GU_OR_INVERTED
  *   - GU_NAND
  *   - GU_SET
  *
  * This operation only has effect if GU_COLOR_LOGIC_OP is enabled.
  *
  * @param context - Pointer to the GUP context
  * @param op - Operation to execute
**/
static inline void sceGupLogicalOp(SceGupContext *context, int op) {
  sceGupSendCommandi(context, LOGIC_OP, op & 0x0f);
}

/**
  * Set ordered pixel dither matrix
  *
  * This dither matrix is only applied if GU_DITHER is enabled.
  *
  * @param context - Pointer to the GUP context
  * @param matrix - Dither matrix
**/
static inline void sceGupSetDither(SceGupContext *context, const ScePspIMatrix4* matrix) {
  sceGupSendCommandi(context, DITH0, (matrix->x.x & 0x0f) | ((matrix->x.y & 0x0f) << 4) | ((matrix->x.z & 0x0f) << 8) | ((matrix->x.w & 0x0f) << 12));
	sceGupSendCommandi(context, DITH1, (matrix->y.x & 0x0f) | ((matrix->y.y & 0x0f) << 4) | ((matrix->y.z & 0x0f) << 8) | ((matrix->y.w & 0x0f) << 12));
	sceGupSendCommandi(context, DITH2, (matrix->z.x & 0x0f) | ((matrix->z.y & 0x0f) << 4) | ((matrix->z.z & 0x0f) << 8) | ((matrix->z.w & 0x0f) << 12));
	sceGupSendCommandi(context, DITH3, (matrix->w.x & 0x0f) | ((matrix->w.y & 0x0f) << 4) | ((matrix->w.z & 0x0f) << 8) | ((matrix->w.w & 0x0f) << 12));
}

/**
  * Set how primitives are shaded
  *
  * The available shading-methods are:
  *   - GU_FLAT - Primitives are flatshaded, the last vertex-color takes effet
  *   - GU_SMOOTH - Primtives are gouraud-shaded, all vertex-colors take effect
  *
  * @param context - Pointer to the GUP context
  * @param mode - Which mode to use
**/
static inline void sceGupShadeModel(SceGupContext *context, int mode) {
  sceGupSendCommandi(context, SHADE_MODE, mode);
}

/**
  * Image transfer using the GE
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @par Example: Copy a fullscreen 32-bit image from RAM to VRAM
  * @code
  * sceGuCopyImage(GU_PSM_8888,0,0,480,272,512,pixels,0,0,512,(void*)(((unsigned int)framebuffer)+0x4000000));
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param psm - Pixel format for buffer
  * @param sx - Source X
  * @param sy - Source Y
  * @param width - Image width
  * @param height - Image height
  * @param srcw - Source buffer width (block aligned)
  * @param src - Source pointer
  * @param dx - Destination X
  * @param dy - Destination Y
  * @param destw - Destination buffer width (block aligned)
  * @param dest - Destination pointer
**/
static inline void sceGupCopyImage(SceGupContext *context, int psm, int sx, int sy, int width, int height, int srcw, void* src, int dx, int dy, int destw, void* dest) {
  sceGupSendCommandi(context, TRANSFER_SRC, ((unsigned int)src));
	sceGupSendCommandi(context, TRANSFER_SRC_W, ((((unsigned int)src) & 0xff000000) >> 8) | srcw);
	sceGupSendCommandi(context, TRANSFER_SRC_OFFSET, (sy << 10) | sx);
	sceGupSendCommandi(context, TRANSFER_DST, ((unsigned int)dest));
	sceGupSendCommandi(context, TRANSFER_DST_W, ((((unsigned int)dest) & 0xff000000) >> 8) | destw);
	sceGupSendCommandi(context, TRANSFER_DST_OFFSET, (dy << 10) | dx);
	sceGupSendCommandi(context, TRANSFER_SIZE, ((height - 1) << 10) | (width - 1));
	sceGupSendCommandi(context, TRANSFER_START, (psm ^ 0x03) ? 0 : 1);
}

/**
  * Specify the texture environment color
  *
  * This is used in the texture function when a constant color is needed.
  *
  * See sceGuTexFunc() for more information.
  *
  * @param context - Pointer to the GUP context
  * @param color - Constant color (0x00BBGGRR)
**/
static inline void sceGupTexEnvColor(SceGupContext *context, unsigned int color) {
  sceGupSendCommandi(context, TEX_ENV_COLOR, color);
}

/**
  * Set how the texture is filtered
  *
  * Available filters are:
  *   - GU_NEAREST
  *   - GU_LINEAR
  *   - GU_NEAREST_MIPMAP_NEAREST
  *   - GU_LINEAR_MIPMAP_NEAREST
  *   - GU_NEAREST_MIPMAP_LINEAR
  *   - GU_LINEAR_MIPMAP_LINEAR
  *
  * @param context - Pointer to the GUP context
  * @param min - Minimizing filter
  * @param mag - Magnifying filter
**/
static inline void sceGupTexFilter(SceGupContext *context, int min, int mag) {
  sceGupSendCommandi(context, TEX_FILTER, (mag << 8) | min);
}

/**
  * Set texture function
  *
  * @param context - Pointer to the GUP context
  * @param func - Function to set
  * @param component - Component to set
  * @param colorDouble - Color double to set
**/
static inline void sceGupPutTexFunc(SceGupContext *context, int func, int component, int colorDouble)
{
	sceGupSendCommandi(context, TEX_FUNC, (colorDouble << 16) | (component << 8) | func);
}

/**
  * Set how textures are applied
  *
  * Key for the apply-modes:
  *   - Cv - Color value result
  *   - Ct - Texture color
  *   - Cf - Fragment color
  *   - Cc - Constant color (specified by sceGuTexEnvColor())
  *
  * Available apply-modes are: (TFX)
  *   - GU_TFX_MODULATE - Cv=Ct*Cf TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_DECAL - TCC_RGB: Cv=Ct,Av=Af TCC_RGBA: Cv=Cf*(1-At)+Ct*At Av=Af
  *   - GU_TFX_BLEND - Cv=(Cf*(1-Ct))+(Cc*Ct) TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_REPLACE - Cv=Ct TCC_RGB: Av=Af TCC_RGBA: Av=At
  *   - GU_TFX_ADD - Cv=Cf+Ct TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *
  * The fields TCC_RGB and TCC_RGBA specify components that differ between
  * the two different component modes.
  *
  *   - GU_TFX_MODULATE - The texture is multiplied with the current diffuse fragment
  *   - GU_TFX_REPLACE - The texture replaces the fragment
  *   - GU_TFX_ADD - The texture is added on-top of the diffuse fragment
  *
  * Available component-modes are: (TCC)
  *   - GU_TCC_RGB - The texture alpha does not have any effect
  *   - GU_TCC_RGBA - The texture alpha is taken into account
  *
  * @param context - Pointer to the GUP context
  * @param tfx - Which apply-mode to use
  * @param tcc - Which component-mode to use
**/
static inline void sceGupTexFunc(SceGupContext *context, int tfx, int tcc) {
  context->state.texture.tfunc_tcc = tcc;
	context->state.texture.tfunc_txf = tfx;
	sceGupPutTexFunc(context, context->state.texture.tfunc_txf, context->state.texture.tfunc_tcc, context->state.texture.tfunc_cd);
}

/**
  * Set current texturemap
  *
  * Textures may reside in main RAM, but it has a huge speed-penalty. Swizzle textures
  * to get maximum speed.
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @param context - Pointer to the GUP context
  * @param mipmap - Mipmap level
  * @param width - Width of texture (must be a power of 2)
  * @param height - Height of texture (must be a power of 2)
  * @param tbw - Texture Buffer Width (block-aligned)
  * @param tbp - Texture buffer pointer (16 byte aligned)
**/
static inline void sceGupTexImage(SceGupContext *context, int mipmap, int width, int height, int tbw, const void* tbp) {
  GECommand texAddr = (GECommand)(TEX_ADDR0 + mipmap);
	GECommand texBufWidth = (GECommand)(TEX_BUF_WIDTH0 + mipmap);
	GECommand texSize = (GECommand)(TEX_SIZE0 + mipmap);
	sceGupSendCommandi(context, texAddr, ((unsigned int)tbp));
	sceGupSendCommandi(context, texBufWidth, ((((unsigned int)tbp) >> 8) & 0x0f0000) | tbw);
	sceGupSendCommandi(context, texSize, (getExp(height) << 8) | (getExp(width)));
	sceGupTexFlush(context);
}

/**
  * Set texture-level mode (mipmapping)
  *
  * Available modes are:
  *   - GU_TEXTURE_AUTO
  *   - GU_TEXTURE_CONST
  *   - GU_TEXTURE_SLOPE
  *
  * @param context - Pointer to the GUP context
  * @param mode - Which mode to use
  * @param bias - Which mipmap bias to use
**/
static inline void sceGupTexLevelMode(SceGupContext *context, unsigned int mode, float bias) {
  int offset = (int)truncf(bias * 16.0f);

	// mip map bias?
	if (offset >= 128)
		offset = 128;
	else if (offset < -128)
		offset = -128;

	sceGupSendCommandi(context, TEX_LEVEL, (((unsigned int)(offset)) << 16) | mode);
}

/**
  * Set the texture-mapping mode
  *
  * Available modes are:
  *   - GU_TEXTURE_COORDS
  *   - GU_TEXTURE_MATRIX
  *   - GU_ENVIRONMENT_MAP
  *
  * @param context - Pointer to the GUP context
  * @param mode - Which mode to use
  * @param lu - Light U
  * @param lv - Light V
**/
static inline void sceGupTexMapMode(SceGupContext *context, int mode, unsigned int lu, unsigned int lv) {
  context->state.texture.tmn = mode & 3;
	sceGupPutTexMap(context, context->state.texture.tmn, context->state.texture.tmi);
	sceGupPutTexShade(context, lu, lv);
}

/**
  * Set texture-mode parameters
  *
  * Available texture-formats are:
  *   - GU_PSM_5650 - Hicolor, 16-bit
  *   - GU_PSM_5551 - Hicolor, 16-bit
  *   - GU_PSM_4444 - Hicolor, 16-bit
  *   - GU_PSM_8888 - Truecolor, 32-bit
  *   - GU_PSM_T4 - Indexed, 4-bit (2 pixels per byte)
  *   - GU_PSM_T8 - Indexed, 8-bit
  *
  * @param context - Pointer to the GUP context
  * @param tpsm - Which texture format to use
  * @param maxmips - Number of mipmaps to use (0-8)
  * @param mc - Multiclut on/off (0/1)
  * @param swizzle - GU_TRUE(1) to swizzle texture-reads
**/
static inline void sceGupTexMode(SceGupContext *context, int tpsm, int maxmips, int mc, int swizzle) {
  int ext = (tpsm>>8) & 1;
	sceGupPutTexMode(context, tpsm, ext, maxmips, mc, swizzle);
}

/**
  * Set texture offset
  *
  * @note Only used by the 3D T&L pipe, renders done with GU_TRANSFORM_2D are
  * not affected by this.
  *
  * @param context - Pointer to the GUP context
  * @param u - Offset to add to the U coordinate
  * @param v - Offset to add to the V coordinate
**/
static inline void sceGupTexOffset(SceGupContext *context, float u, float v) {
  sceGupSendCommandf(context, TEX_OFFSET_U, u);
	sceGupSendCommandf(context, TEX_OFFSET_V, v);
}

/**
  * Set texture projection-map mode
  *
  * Available modes are:
  *   - GU_POSITION
  *   - GU_UV
  *   - GU_NORMALIZED_NORMAL
  *   - GU_NORMAL
  *
  * @param context - Pointer to the GUP context
  * @param mode - Which mode to use
**/
static inline void sceGupTexProjMapMode(SceGupContext *context, int mode) {
  context->state.texture.tmi = mode & 3;
	sceGupPutTexMap(context, context->state.texture.tmn, context->state.texture.tmi);
}

/**
  * Set texture scale
  *
  * @note Only used by the 3D T&L pipe, renders ton with GU_TRANSFORM_2D are
  * not affected by this.
  *
  * @param u - Scalar to multiply U coordinate with
  * @param v - Scalar to multiply V coordinate with
**/
static inline void sceGupTexScale(SceGupContext *context, float u, float v) {
  sceGupSendCommandf(context, TEX_SCALE_U, u);
	sceGupSendCommandf(context, TEX_SCALE_V, v);
}

/**
  * Set texture slope
  *
  * @param context - Pointer to the GUP context
  * @param slope - Slope to use
**/
static inline void sceGupTexSlope(SceGupContext *context, float slope) {
  sceGupSendCommandf(context, TEX_LOD_SLOPE, slope);
}

/**
  * Synchronize rendering pipeline with image upload.
  *
  * This will stall the rendering pipeline until the current image upload initiated by
  * sceGuCopyImage() has completed.
  *
  * @param context - Pointer to the GUP context
**/
static inline void sceGupTexSync(SceGupContext *context) {
  sceGupSendCommandi(context, TEX_SYNC, 0);
}

/**
  * Set if the texture should repeat or clamp
  *
  * Available modes are:
  *   - GU_REPEAT - The texture repeats after crossing the border
  *   - GU_CLAMP - Texture clamps at the border
  *
  * @param context - Pointer to the GUP context
  * @param u - Wrap-mode for the U direction
  * @param v - Wrap-mode for the V direction
**/
static inline void sceGupTexWrap(SceGupContext *context, int u, int v) {
  sceGupSendCommandi(context, TEX_WRAP, (v << 8) | (u));
}

/**
  * Upload CLUT (Color Lookup Table)
  *
  * @note Data must be aligned to 1 quad word (16 bytes)
  *
  * @param context - Pointer to the GUP context
  * @param num_blocks - How many blocks of 8 entries to upload (32*8 is 256 colors)
  * @param cbp - Pointer to palette (16 byte aligned)
**/
static inline void sceGupClutLoad(SceGupContext *context, int num_blocks, const void* cbp) {
  sceGupSendCommandi(context, CLUT_BUF_PTR, ((unsigned int)cbp));
	sceGupSendCommandi(context, CLUT_BUF_WIDTH, (((unsigned int)cbp) >> 8) & 0xf0000);
	sceGupSendCommandi(context, CLUT_LOAD, num_blocks);
}

/**
  * Set current CLUT mode
  *
  * Available pixel formats for palettes are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @param context - Pointer to the GUP context
  * @param cpsm - Which pixel format to use for the palette
  * @param shift - Shifts color index by that many bits to the right
  * @param mask - Masks the color index with this bitmask after the shift (0-0xFF)
  * @param csa - Read-out start location (16-palette units)
**/
static inline void sceGupClutMode(SceGupContext *context, unsigned int cpsm, unsigned int shift, unsigned int mask, unsigned int csa) {
  unsigned int argument = (cpsm) | (shift << 2) | (mask << 8) | (csa << 16);
	sceGupSendCommandi(context, CLUT_FORMAT, argument);
}

/**
  * Set virtual coordinate offset
  *
  * The PSP has a virtual coordinate-space of 4096x4096, this controls where rendering is performed
  *
  * @par Example: Center the virtual coordinate range
  * @code
  * sceGuOffset(2048-(480/2),2048-(480/2));
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param x - Offset (0-4095)
  * @param y - Offset (0-4095)
**/
static inline void sceGupOffset(SceGupContext *context, unsigned int x, unsigned int y) {
  sceGupSendCommandi(context, OFFSET_X, x << 4);
	sceGupSendCommandi(context, OFFSET_Y, y << 4);
}

/**
  * Set the scissor region
  *
  * @param context - Pointer to the GUP context
  * @param sx1 - X coordinate of the top-left corner
  * @param sy1 - Y coordinate of the top-left corner
  * @param sx2 - X coordinate of the bottom-right corner 
  * @param sy2 - Y coordinate of the bottom-right corner
**/
static inline void sceGupPutScissorRegion(SceGupContext *context, int sx1, int sy1, int sx2, int sy2)
{
  int xy1 = (sx1 << 10) | sy1;
	int xy2 = (sx2 << 10) | sy2;

	sceGupSendCommandi(context, SCISSOR1, xy1);
	sceGupSendCommandi(context, SCISSOR2, xy2);
	sceGupSendCommandi(context, REGION1, 0);
	sceGupSendCommandi(context, REGION2, xy2);
}

/**
  * Set what to scissor within the current viewport
  *
  * Note that scissoring is only performed if the custom scissoring is enabled (GU_SCISSOR_TEST)
  *
  * @param context - Pointer to the GUP context
  * @param x - Left of scissor region
  * @param y - Top of scissor region
  * @param w - Width of scissor region
  * @param h - Height of scissor region
**/
static inline void sceGupScissor(SceGupContext *context, int x, int y, int w, int h) {
  int sx1, sy1, sx2, sy2;

	sx1 = x;
	sy1 = y;
	sx2 = x + w - 1;
	sy2 = y + h - 1;

	context->state.scissor.x1 = sx1;
	context->state.scissor.y1 = sy1;
	context->state.scissor.x2 = sx2;
	context->state.scissor.y2 = sy2;

	if (context->state.scissor.en != 0) {
		sceGupPutScissorRegion(context, sx1, sy1, sx2, sy2);
	}
}

/**
  * Set current viewport
  *
  * @par Example: Setup a viewport of size (480,272) with origo at (2048,2048)
  * @code
  * sceGuViewport(2048,2048,480,272);
  * @endcode
  *
  * @param context - Pointer to the GUP context
  * @param cx - Center for horizontal viewport
  * @param cy - Center for vertical viewport
  * @param width - Width of viewport
  * @param height - Height of viewport
**/
static inline void sceGupViewport(SceGupContext *context, int cx, int cy, int width, int height) {
  float sx, sy, tx, ty;
  sx = (float)(width)  *  0.5f;
	sy = (float)(height) * -0.5f;
	tx = (float)cx;
	ty = (float)cy;

	sceGupSendCommandf(context, VIEWPORT_X_SCALE, sx);
	sceGupSendCommandf(context, VIEWPORT_Y_SCALE, sy);
	sceGupSendCommandf(context, VIEWPORT_X_CENTER, tx);
	sceGupSendCommandf(context, VIEWPORT_Y_CENTER, ty);
}

/**
  * Draw bezier surface
  *
  * @param context - Pointer to the GUP context
  * @param vtype - Vertex type, look at sceGuDrawArray() for vertex definition
  * @param ucount - Number of vertices used in the U direction
  * @param vcount - Number of vertices used in the V direction
  * @param indices - Pointer to index buffer
  * @param vertices - Pointer to vertex buffer
**/
static inline void sceGupDrawBezier(SceGupContext *context, int vtype, int ucount, int vcount, const void* indices, const void* vertices) {
  if (vtype)
    sceGupSendCommandi(context, VERTEX_TYPE, vtype);

  if (indices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, IADDR, (unsigned int)indices);
  }

  if (vertices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, VADDR, (unsigned int)vertices);
  }

  sceGupSendCommandi(context, BEZIER, (vcount << 8) | ucount);
}

/**
  * Set dividing for patches (beziers and splines)
  *
  * @param context - Pointer to the GUP context
  * @param ulevel - Number of division on u direction
  * @param vlevel - Number of division on v direction
**/
static inline void sceGupPatchDivide(SceGupContext *context, unsigned int ulevel, unsigned int vlevel) {
  sceGupSendCommandi(context, PATCH_DIVISION, (vlevel << 8) | ulevel);
}

/**
  * Set front face for patches (beziers and splines)
  *
  * @param context - Pointer to the GUP context
  * @param mode - Desired front face mode (GU_CW | GU_CCW)
**/
static inline void sceGupPatchFrontFace(SceGupContext *context, unsigned int mode) {
  sceGupSendCommandi(context, PATCH_FACING, mode);
}

/**
  * Set primitive for patches (beziers and splines)
  *
  * @param context - Pointer to the GUP context
  * @param prim - Desired primitive type (GU_POINTS | GU_LINE_STRIP | GU_TRIANGLE_STRIP)
**/
static inline void sceGupPatchPrim(SceGupContext *context, int prim) {
  switch (prim)
	{
	case GU_POINTS:
		sceGupSendCommandi(context, PATCH_PRIMITIVE, 2);
		break;
	case GU_LINE_STRIP:
		sceGupSendCommandi(context, PATCH_PRIMITIVE, 1);
		break;
	case GU_TRIANGLE_STRIP:
		sceGupSendCommandi(context, PATCH_PRIMITIVE, 0);
		break;
	}

}

/**
  * Set transform matrices
  *
  * Available matrices are:
  *   - GU_PROJECTION - View->Projection matrix
  *   - GU_VIEW - World->View matrix
  *   - GU_MODEL - Model->World matrix
  *   - GU_TEXTURE - Texture matrix
  *
  * @param context - Pointer to the GUP context
  * @param type - Which matrix-type to set
  * @param matrix - Matrix to load
**/
static inline void sceGupSetMatrix(SceGupContext *context, int type, const ScePspFMatrix4* matrix) {
  unsigned int i, j;
	const float *fmatrix = (const float *)matrix;

	switch (type)
	{
	case GU_PROJECTION:
	{
		sceGupSendCommandf(context, PROJ_MATRIX_NUMBER, 0);

		// 4*4 - most probably projection
		for (i = 0; i < 16; ++i)
			sceGupSendCommandf(context, PROJ_MATRIX_DATA, fmatrix[i]);
	}
	break;

	case GU_VIEW:
	{
		sceGupSendCommandf(context, VIEW_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - view matrix?
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sceGupSendCommandf(context, VIEW_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;

	case GU_MODEL:
	{
		sceGupSendCommandf(context, WORLD_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - ???
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sceGupSendCommandf(context, WORLD_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;

	case GU_TEXTURE:
	{
		sceGupSendCommandf(context, TGEN_MATRIX_NUMBER, 0);

		// 4*4 -> 3*4 - ???
		for (i = 0; i < 4; ++i)
		{
			for (j = 0; j < 3; ++j)
				sceGupSendCommandf(context, TGEN_MATRIX_DATA, fmatrix[j + i * 4]);
		}
	}
	break;
	}
}

/**
  * Specify skinning matrix entry
  *
  * To enable vertex skinning, pass GU_WEIGHTS(n), where n is between
  * 1-8, and pass available GU_WEIGHT_??? declaration. This will change
  * the amount of weights passed in the vertex araay, and by setting the skinning,
  * matrices, you will multiply each vertex every weight and vertex passed.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param context - Pointer to the GUP context
  * @param index - Skinning matrix index (0-7)
  * @param matrix - Matrix to set
**/
static inline void sceGupBoneMatrix(SceGupContext *context, unsigned int index, const ScePspFMatrix4* matrix) {
  unsigned int offset = ((index << 1) + index) << 2; // 3*4 matrix
	unsigned int i, j;
	const float *fmatrix = (const float *)matrix;

	sceGupSendCommandi(context, BONE_MATRIX_NUMBER, offset);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 3; ++j) {
			sceGupSendCommandf(context, BONE_MATRIX_DATA, fmatrix[j + (i << 2)]);
		}
	}
}

/**
  * Specify morph weight entry
  *
  * To enable vertex morphing, pass GU_VERTICES(n), where n is between
  * 1-8. This will change the amount of vertices passed in the vertex array,
  * and by setting the morph weights for every vertex entry in the array,
  * you can blend between them.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param context - Pointer to the GUP context
  * @param index - Morph weight index (0-7)
  * @param weight - Weight to set
**/
static inline void sceGupMorphWeight(SceGupContext *context, unsigned int index, float weight) {
  sceGupSendCommandf(context, MORPH_WEIGHT0 + index, weight);
}

/**
  * Draw an array of primitives
  *
  * @param context - Pointer to the GUP context
  * @param primitive_type - Type of primitive to draw
  * @param vertex_type - Type of vertex to draw
  * @param vcount - Number of vertices to draw
  * @param primcount - Number of primitives to draw
  * @param indices - Pointer to index buffer
  * @param vertices - Pointer to vertex buffer
**/
static inline void sceGupDrawArrayN(SceGupContext *context, int primitive_type, int vertex_type, int vcount, int primcount, const void* indices, const void* vertices) {
  if (vertex_type)
		sceGupSendCommandi(context, VERTEX_TYPE, vertex_type);

	if (indices)
	{
		sceGupSendCommandi(context, BASE, (((unsigned int)indices) >> 8) & 0xf0000);
		sceGupSendCommandi(context, IADDR, (unsigned int)indices);
	}

	if (vertices)
	{
		sceGupSendCommandi(context, BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
		sceGupSendCommandi(context, VADDR, (unsigned int)vertices);
	}

	if (primcount > 0)
	{
		int i;
		for (i = 0; i < primcount; i++)
			sceGupSendCommandi(context, PRIM, (primitive_type << 16) | vcount);
	}
}

/**
  * Signal a call to a list
  *
  * @param context - Pointer to the GUP context
  * @param list_addr - Address of the list to call
**/
static inline void sceGupSignalCall(SceGupContext *context, unsigned int list_addr) {
  sceGupSendCommandi(context, SIGNAL, (list_addr >> 16) | 0x110000);
  sceGupSendCommandi(context, END, list_addr & 0xffff);
}

/**
  * Call a list
  *
  * @param context - Pointer to the GUP context
  * @param list_addr - Address of the list to call
**/
static inline void sceGupCall(SceGupContext *context, unsigned int list_addr) {
  sceGupSendCommandi(context, BASE, (list_addr >> 8) & 0xf0000);
  sceGupSendCommandi(context, CALL, list_addr);
}

/**
  * Get the current size of the list in the GUP context
  *
  * @param context - Pointer to the GUP context
  * @return The current size of the list in the GUP context
**/
static inline int sceGupGetCurrentSize(SceGupContext *context) {
  return ((unsigned int)context->list.current) - ((unsigned int)context->list.start);
}

/**
  * Clear the GUP context
  *
  * @param context - Pointer to the GUP context
  * @param flags - Flags to clear
**/
static inline void sceGupClear(SceGupContext *context, unsigned int flags) {
	unsigned int filter;
	struct Vertex
	{
		u32 color;
		u16 x, y, z;
		u16 pad;
	};

	switch (context->state.fbuf.fpf)
	{
	case GU_PSM_5650:
		filter = context->state.clear.color & 0xffffff;
		break;
	case GU_PSM_5551:
		filter = (context->state.clear.color & 0xffffff) | (context->state.clear.stencil << 31);
		break;
	case GU_PSM_4444:
		filter = (context->state.clear.color & 0xffffff) | (context->state.clear.stencil << 28);
		break;
	case GU_PSM_8888:
		filter = (context->state.clear.color & 0xffffff) | (context->state.clear.stencil << 24);
		break;
	default:
		filter = 0;
		break;
	}

	struct Vertex *vertices;
	int count;

	if (!(flags & GU_FAST_CLEAR_BIT))
	{
		vertices = (struct Vertex *)sceGupGetMemory(context, 2 * sizeof(struct Vertex));
		count = 2;

		vertices[0].color = filter;
		vertices[0].x = context->state.scissor.x1;
		vertices[0].y = context->state.scissor.y1;
		vertices[0].z = context->state.clear.depth;

		vertices[1].color = filter;
		vertices[1].x = (context->state.scissor.x2 - context->state.scissor.x1 + 1);
		vertices[1].y = (context->state.scissor.y2 - context->state.scissor.y1 + 1);
		vertices[1].z = context->state.clear.depth;
	}
	else
	{
		struct Vertex *curr;
		unsigned int i, blockWidth;
    // Use blockWidth of 32 for 8888, 64 for other formats
    blockWidth = context->state.fbuf.fpf == GU_PSM_8888 ? 32 : 64;
		count = ((context->state.fbuf.width + blockWidth - 1) / blockWidth) * 2;
		vertices = (struct Vertex *)sceGupGetMemory(context, count * sizeof(struct Vertex));
		curr = vertices;

		for (i = 0; i < count; ++i, ++curr)
		{
			unsigned int j, k;

			j = i >> 1;
			k = (i & 1);

			curr->color = filter;
			curr->x = (j + k) * blockWidth;
			curr->y = k * context->state.fbuf.height;
			curr->z = context->state.clear.depth;
		}
	}

	sceGupSendCommandi(context, CLEAR_MODE, ((flags & (GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT)) << 8) | 0x01);
	sceGupDrawArray(context, GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, count, 0, vertices);
	sceGupSendCommandi(context, CLEAR_MODE, 0);
}

/**
  * Set the alpha test status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetAlphaTestStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, ALPHA_TEST_ENABLE, status);
}

/**
  * Set the depth test status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetDepthTestStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, Z_TEST_ENABLE, status);
}

/**
  * Set the scissor test status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetScissorTestStatus(SceGupContext *context, unsigned int status) {
  if (status != 0) {
		context->state.scissor.en = 1;
		sceGupPutScissorRegion(context, context->state.scissor.x1, context->state.scissor.y1, context->state.scissor.x2, context->state.scissor.y2);
	} else {
		context->state.scissor.en = 0;
		sceGupPutScissorRegion(context, 0, 0, (context->state.fbuf.width - 1), (context->state.fbuf.height - 1));
	}
}

/**
  * Set the stencil test status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetStencilTestStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, STENCIL_TEST_ENABLE, status);
}

/**
  * Set the blend status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetBlendStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, ALPHA_BLEND_ENABLE, status);
}

/**
  * Set the cull face status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetCullFaceStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, CULL_FACE_ENABLE, status);
}

/**
  * Set the dither status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetDitherStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, DITHER_ENABLE, status);
}

/**
  * Set the fog status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetFogStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, FOG_ENABLE, status);
}

/**
  * Set the clip planes status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetClipPlanesStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, DEPTH_CLIP_ENABLE, status);
}

/**
  * Set the texture 2D status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetTexture2DStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, TEXTURE_ENABLE, status);
}

/**
  * Set the lighting status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLightingStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LIGHTING_ENABLE, status);
}

/**
  * Set the light 0 status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLight0Status(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LIGHT_ENABLE0, status);
}

/**
  * Set the light 1 status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLight1Status(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LIGHT_ENABLE1, status);
}

/**
  * Set the light 2 status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLight2Status(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LIGHT_ENABLE2, status);
}

/**
  * Set the light 3 status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLight3Status(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LIGHT_ENABLE3, status);
}

/**
  * Set the line smooth status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetLineSmoothStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, ANTI_ALIAS_ENABLE, status);
}

/**
  * Set the patch cull face status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetPatchCullFaceStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, PATCH_CULL_ENABLE, status);
}

/**
  * Set the color test status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetColorTestStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, COLOR_TEST_ENABLE, status);
}

/**
  * Set the color logic op status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetColorLogicOpStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, LOGIC_OP_ENABLE, status);
}

/**
  * Set the face normal reverse status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetFaceNormalReverseStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, NORMAL_REVERSE, status);
}

/**
  * Set the patch face status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetPatchFaceStatus(SceGupContext *context, unsigned int status) {
  sceGupSendCommandi(context, PATCH_FACING, status);
}

/**
  * Set the color double status
  *
  * @param context - Pointer to the GUP context
  * @param status - Status to set
**/
static inline void sceGupSetColorDoubleStatus(SceGupContext *context, unsigned int status) {
  if (status!=0) {
		context->state.texture.tfunc_cd = 1;
	} else {
		context->state.texture.tfunc_cd = 0;
	}
	sceGupPutTexFunc(context, context->state.texture.tfunc_txf, context->state.texture.tfunc_tcc, context->state.texture.tfunc_cd);
}

/**
  * Set a state
  *
  * @param context - Pointer to the GUP context
  * @param state - State to set
  * @param status - Status to set
**/
static inline void sceGupSetStatus(SceGupContext *context, unsigned int state, unsigned int status) {
  switch (state)
	{
	case GU_ALPHA_TEST:
		sceGupSetAlphaTestStatus(context, status);
		break;
	case GU_DEPTH_TEST:
		sceGupSetDepthTestStatus(context, status);
		break;
	case GU_SCISSOR_TEST:
		sceGupSetScissorTestStatus(context, status);
	  break;
	case GU_STENCIL_TEST:
		sceGupSetStencilTestStatus(context, status);
		break;
	case GU_BLEND:
		sceGupSetBlendStatus(context, status);
		break;
	case GU_CULL_FACE:
		sceGupSetCullFaceStatus(context, status);
		break;
	case GU_DITHER:
		sceGupSetDitherStatus(context, status);
		break;
	case GU_FOG:
		sceGupSetFogStatus(context, status);
		break;
	case GU_CLIP_PLANES:
		sceGupSetClipPlanesStatus(context, status);
		break;
	case GU_TEXTURE_2D:
		sceGupSetTexture2DStatus(context, status);
		break;
	case GU_LIGHTING:
		sceGupSetLightingStatus(context, status);
		break;
	case GU_LIGHT0:
		sceGupSetLight0Status(context, status);
		break;
	case GU_LIGHT1:
		sceGupSetLight1Status(context, status);
		break;
	case GU_LIGHT2:
		sceGupSetLight2Status(context, status);
		break;
	case GU_LIGHT3:
		sceGupSetLight3Status(context, status);
		break;
	case GU_LINE_SMOOTH:
		sceGupSetLineSmoothStatus(context, status);
		break;
	case GU_PATCH_CULL_FACE:
		sceGupSetPatchCullFaceStatus(context, status);
		break;
	case GU_COLOR_TEST:
		sceGupSetColorTestStatus(context, status);
		break;
	case GU_COLOR_LOGIC_OP:
		sceGupSetColorLogicOpStatus(context, status);
		break;
	case GU_FACE_NORMAL_REVERSE:
		sceGupSetFaceNormalReverseStatus(context, status);
		break;
	case GU_PATCH_FACE:
		sceGupSetPatchFaceStatus(context, status);
		break;
	case GU_COLOR_DOUBLE:
		sceGupSetColorDoubleStatus(context, status);
	  break;
	}
}
/**
  * Disable a state
  *
  * @param context - Pointer to the GUP context
  * @param state - State to disable
**/
static inline void sceGupDisable(SceGupContext *context, unsigned int state) {
    sceGupSetStatus(context, state, 0);
}

/**
  * Enable a state
  *
  * @param context - Pointer to the GUP context
  * @param state - State to enable
**/
static inline void sceGupEnable(SceGupContext *context, unsigned int state) {
    sceGupSetStatus(context, state, 1);
}


/**
  * Draw a spline
  *
  * @param context - Pointer to the GUP context
  * @param vertex_type - Type of vertex to draw
  * @param ucount - Number of u-vertices to draw
  * @param vcount - Number of v-vertices to draw
  * @param uedge - Number of u-edges to draw
  * @param vedge - Number of v-edges to draw
  * @param indices - Pointer to index buffer
  * @param vertices - Pointer to vertex buffer
**/
static inline void sceGupDrawSpline(SceGupContext *context, int vertex_type, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices) {
  if (vertex_type)
    sceGupSendCommandi(context, VERTEX_TYPE, vertex_type);

  if (indices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)indices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, IADDR, (unsigned int)indices);
  }

  if (vertices)
  {
    sceGupSendCommandi(context, BASE, (((unsigned int)vertices) >> 8) & 0xf0000);
    sceGupSendCommandi(context, VADDR, (unsigned int)vertices);
  }

  sceGupSendCommandi(context, SPLINE, (vedge << 18) | (uedge << 16) | (vcount << 8) | ucount);
}


/**
  * Signal a return from a list
  *
  * @param context - Pointer to the GUP context
  * @param id - ID of the list to signal
**/
static inline void sceGupSignalRet(SceGupContext *context, unsigned int id) {
  sceGupSendCommandi(context, SIGNAL, 0x120000);
  sceGupSendCommandi(context, END, 0);
}

/**
  * Return from a list
  *
  * @param context - Pointer to the GUP context
**/
static inline void sceGupRet(SceGupContext *context) {
  sceGupSendCommandi(context, RET, 0);
}

/**
  * Set the fog
  *
  * @param context - Pointer to the GUP context
  * @param near - Near distance
  * @param far - Far distance
**/
static inline void sceGupFog(SceGupContext *context, float near, float far, unsigned int color) {
  float distance = far - near;

	if (distance)
		distance = 1.0f / distance;

	sceGupSendCommandi(context, FOG_COLOR, color);
	sceGupSendCommandf(context, FOG1, far);
	sceGupSendCommandf(context, FOG2, distance);
}

/**
  * Set the frame buffer
  *
  * @param context - Pointer to the GUP context
  * @param psm - Pixel size
  * @param fbp - Frame buffer pointer
**/
static inline void sceGupSetFrameBuffer(SceGupContext *context, int fpf, int width, int height) {
  context->state.fbuf.fpf = fpf;
  context->state.fbuf.width = width;
  context->state.fbuf.height = height;
}

/**@}*/

#if defined(__cplusplus)
};
#endif

#endif
