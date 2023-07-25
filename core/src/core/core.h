#ifndef CORE_H
#define CORE_H

// Base Types

#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

#define local_variable  static
#define global_variable static
#define internal        static

#define Bytes(value)     (value)
#define Kilobytes(value) (value << 10)
#define Megabytes(value) (value << 20)
#define Gigabytes(value) ((u64)(value) << 30)
#define Terabytes(value) ((u64)(value) << 40)

#define ArrayCount(a) (sizeof((a)) / sizeof(*(a)))

// Platform Types

#ifdef __linux__
#define PLATFORM_LINUX
#elif defined(__WIN32__)
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX
#define PLATFORM_LIB_EXT "so"
#define PLATFORM_SLASH   '/'
#elif defined(PLATFORM_WINDOWS)
#define PLATFORM_LIB_EXT "dll"
#define PLATFORM_SLASH   '\\'
#endif

#ifdef PLATFORM_LINUX
#define CEXPORT __attribute__((visibility("default")))
#define CIMPORT
#elif defined(PLATFORM_WINDOWS)
#define CEXPORT __declspec(dllexport)
#define CIMPORT __declspec(dllimport)
#endif

// Core Interface

typedef struct CCoreState CCoreState;

CEXPORT void core_startup(void);
CEXPORT void core_update(void);
CEXPORT void core_shutdown(void);
CEXPORT b8   core_poll_event(void);
CEXPORT void core_sleep(u32 ms);
CEXPORT u64  core_perf_counter(void);
CEXPORT u64  core_perf_frequency(void);

// Container Interface

CEXPORT u64 hash_string_fnv1a64(const char *str);

// CString8

typedef struct CString8
{
    u8 *str;
    u64 size;
} CString8;

CEXPORT CString8 str8(const char *c);
CEXPORT b8       str8_eq(const CString8 left, const CString8 right);

#define str8_c(s) (const char *)s.str

// CVector2

typedef union CVector2
{
    struct
    {
        f32 x, y;
    };

    struct
    {
        f32 u, v;
    };

    struct
    {
        f32 left, right;
    };

    struct
    {
        f32 width, height;
    };

    f32 elements[2];
} CVector2;

CEXPORT CVector2 v2(f32 x, f32 y);
CEXPORT CVector2 v2_add(CVector2 left, CVector2 right);
CEXPORT CVector2 v2_addf(CVector2 left, f32 right);
CEXPORT CVector2 v2_sub(CVector2 left, CVector2 right);
CEXPORT CVector2 v2_subf(CVector2 left, f32 right);
CEXPORT CVector2 v2_mul(CVector2 left, CVector2 right);
CEXPORT CVector2 v2_mulf(CVector2 left, f32 right);
CEXPORT CVector2 v2_div(CVector2 left, CVector2 right);
CEXPORT CVector2 v2_divf(CVector2 left, f32 right);
CEXPORT f32      v2_dot(CVector2 left, CVector2 right);
CEXPORT b8       v2_eq(CVector2 left, CVector2 right);
CEXPORT CVector2 v2_norm(CVector2 v);
CEXPORT f32      v2_sqrt_len(CVector2 v);
CEXPORT f32      v2_len(CVector2 v);
CEXPORT CVector2 v2_lerp(CVector2 left, CVector2 right, f32 time);

// CVector3

typedef union CVector3
{
    struct
    {
        f32 x, y, z;
    };

    struct
    {
        f32 u, v, w;
    };

    struct
    {
        f32 r, g, b;
    };

    struct
    {
        CVector2 xy;
        f32      _ignored0;
    };

    struct
    {
        f32      _ignored1;
        CVector2 yz;
    };

    struct
    {
        CVector2 uv;
        f32      _ignored2;
    };

    struct
    {
        f32      _ignored3;
        CVector2 vw;
    };

    f32 elements[3];
} CVector3;

CEXPORT CVector3 v3(f32 x, f32 y, f32 z);
CEXPORT CVector3 v3_add(CVector3 left, CVector3 right);
CEXPORT CVector3 v3_sub(CVector3 left, CVector3 right);
CEXPORT CVector3 v3_mul(CVector3 left, CVector3 right);
CEXPORT CVector3 v3_mulf(CVector3 left, f32 right);
CEXPORT CVector3 v3_div(CVector3 left, CVector3 right);
CEXPORT CVector3 v3_divf(CVector3 left, f32 right);
CEXPORT f32      v3_dot(CVector3 left, CVector3 right);
CEXPORT b8       v3_eq(CVector3 left, CVector3 right);
CEXPORT CVector3 v3_norm(CVector3 v);
CEXPORT f32      v3_sqrt_len(CVector3 v);
CEXPORT f32      v3_len(CVector3 v);
CEXPORT CVector3 v3_lerp(CVector3 left, CVector3 right, f32 time);

// CVector4

typedef union CVector4
{
    struct
    {
        union
        {
            CVector3 xyz;
            struct
            {
                f32 x, y, z;
            };
        };

        f32 w;
    };

    struct
    {
        union
        {
            CVector3 rgb;
            struct
            {
                f32 r, g, b;
            };
        };

        f32 a;
    };

    struct
    {
        CVector2 xy;
        f32      _ignored0;
        f32      _ignored1;
    };

    struct
    {
        f32      _ignored2;
        CVector2 yz;
        f32      _ignored3;
    };

    struct
    {
        f32      _ignored4;
        f32      _ignored5;
        CVector2 zw;
    };

    struct
    {
        f32 left, right, top, botton;
    };

    struct
    {
        f32 _ignored6;
        f32 _ignored7;
        f32 width, height;
    };

    f32 elements[4];
} CVector4;

CEXPORT CVector4 v4(f32 x, f32 y, f32 z, f32 w);
CEXPORT CVector4 v4_add(CVector4 left, CVector4 right);
CEXPORT CVector4 v4_sub(CVector4 left, CVector4 right);
CEXPORT CVector4 v4_mul(CVector4 left, CVector4 right);
CEXPORT CVector4 v4_mulf(CVector4 left, f32 right);
CEXPORT CVector4 v4_div(CVector4 left, CVector4 right);
CEXPORT CVector4 v4_divf(CVector4 left, f32 right);
CEXPORT f32      v4_dot(CVector4 left, CVector4 right);
CEXPORT b8       v4_eq(CVector4 left, CVector4 right);
CEXPORT CVector4 v4_norm(CVector4 v);
CEXPORT f32      v4_sqrt_len(CVector4 v);
CEXPORT f32      v4_len(CVector4 v);
CEXPORT CVector4 v4_lerp(CVector4 left, CVector4 right, f32 time);

// Asset Interface

typedef struct CImage CImage;
typedef struct CAsset CAsset;

CEXPORT void    asset_init(void);
CEXPORT void    asset_destroy(void);
CEXPORT void   *asset_file_rw_data_load(const char *file_path);
CEXPORT CImage *asset_image_load(const char *file_path);
CEXPORT void    asset_image_unload(CImage *image);
CEXPORT void    asset_image_size_get(CImage *image, i16 *width, i16 *height);

// Audio Interface

typedef struct CAudio CAudio;

CEXPORT void    audio_init(void);
CEXPORT CAudio *audio_load(const char *file_path);
CEXPORT void    audio_unload(CAudio *audio_state);
CEXPORT void    audio_play(CAudio *audio_state, bool loop);
CEXPORT void    audio_stop(CAudio *audio_state);

// Debug Interface

typedef struct CDebugState CDebugState;

CEXPORT void debug_startup(void);
CEXPORT void debug_shutdown(void);
CEXPORT void debug_update(void);

CEXPORT void debug_memory_handle(void);

CEXPORT void *_debug_memory_alloc(u64 size, const char *file_path, u64 line);
CEXPORT void _debug_memory_free(void *memory, const char *file_path, u64 line);
CEXPORT void _debug_memory_zero(void *memory, u64 size, const char *file_path,
                                u64 line);
CEXPORT void _debug_memory_copy(void *dest, void *src, u64 size,
                                const char *file_path, u64 line);

CEXPORT void *_debug_profiler_timed_block_begin(const char *func_name);
CEXPORT void  _debug_profiler_timed_block_end(void *counter_ptr,
                                              u64   cycle_count);

#define PROFILER_BEGIN(NAME)                                                  \
    void *current_counter_##NAME = _debug_profiler_timed_block_begin(#NAME);  \
    u64   start_##NAME           = core_perf_counter();

#define PROFILER_END(NAME)                                                    \
    u64 end_##NAME = core_perf_counter();                                     \
    _debug_profiler_timed_block_end(current_counter_##NAME,                   \
                                    end_##NAME - start_##NAME);

// Entity Interface

typedef char *CEntityID;

typedef enum CEntityFlags
{
    EntityFlag_Active     = 1 << 0,
    EntityFlag_Renderable = 1 << 1,
    EntityFlag_Everything = 0xFFFFFFFF,
} CEntityFlags;

typedef struct CEntity
{
    CEntityID    uuid;
    CEntityFlags flags;
    b8           enabled;

    CVector3 position;
    CVector4 quaternion;
    CVector3 scale;
} CEntity;

// Scene Interface

#define SCENE_ENTITIES_MAX 1000

typedef struct CSceneState
{
    char *path;
    b8    edited;
    b8    dirtied;

    CEntityID *entities_selected;
    u64        entities_selected_count;
    CEntity   *entities;
    u64        entities_count;
} CSceneState;

CEXPORT void scene_startup(void);
CEXPORT void scene_update(f32 dt);
CEXPORT void scene_shutdown(void);

CEXPORT CEntity *scene_entity_create(void);
CEXPORT void     scene_entity_destroy(CEntity *entity);

// UUID Interface
CEXPORT char *uuid_gen(void); // NOTE: allocates memory!

// Window Interface

typedef struct CWindow CWindow;

CEXPORT CWindow *window_open(const char *title, i32 xpos, i32 ypos, i32 width,
                             i32 height);
CEXPORT void     window_close(CWindow *window);
CEXPORT b8       window_poll_events(void);

// Event Interface

typedef enum CEventCode
{
    EventCode_AppQuit        = 1 << 0,
    EventCode_KeyPressed     = 1 << 1,
    EventCode_KeyReleased    = 1 << 2,
    EventCode_ButtonPressed  = 1 << 3,
    EventCode_ButtonReleased = 1 << 4,
    EventCode_MouseMotion    = 1 << 5,
    EventCode_MouseWheel     = 1 << 6,
    EventCode_WindowResized  = 1 << 7,
    EventCode_WindowClosed   = 1 << 8,
    EventCode_Everything     = 0xFFFFFFFF,
    EventCode_Count          = 9,
} CEventCode;

typedef struct CEvent
{
    // 128 bites
    union
    {
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
} CEvent;

typedef b8 (*event_on_listener)(u32 code, CEvent event);

CEXPORT b8 event_startup(void);
CEXPORT b8 event_shutdown(void);
CEXPORT b8 event_register(u32 code, event_on_listener on_listener);
CEXPORT b8 event_unregister(u32 code, event_on_listener on_listener);
CEXPORT b8 event_fire(u32 code, CEvent event);

// Input Interface

typedef enum CMouseButton
{
    MouseButton_Left,
    MouseButton_Middle,
    MouseButton_Right,
    MouseButton_Count,
} CMouseButton;

typedef enum CKeyCode
{
    KeyCode_A,
    KeyCode_D,
    KeyCode_W,
    KeyCode_S,
    KeyCode_Q,
    KeyCode_E,
    KeyCode_Escape,
    KeyCode_Count,
} CKeyCode;

typedef struct CKeyboardState
{
    b8 keys[KeyCode_Count];
} CKeyboardState;

typedef struct CMouseState
{
    i32 x, y;
    i32 wheel;
    b8  buttons[MouseButton_Count];
} CMouseState;

typedef struct CInputState
{
    CKeyboardState keyboard_current;
    CKeyboardState keyboard_previous;

    CMouseState mouse_current;
    CMouseState mouse_previous;
} CInputState;

CEXPORT void input_startup(void);
CEXPORT void input_shutdown(void);

CEXPORT void input_button_process(u32 button, b8 pressed);
CEXPORT void input_key_process(u32 key, b8 pressed);
CEXPORT void input_mouse_motion_process(i32 x, i32 y);
CEXPORT void input_mouse_scroll_process(i32 delta);

CEXPORT void input_update(void);
CEXPORT b8   input_button_pressed(u32 button);
CEXPORT b8   input_button_down(u32 button);
CEXPORT b8   input_button_up(u32 button);
CEXPORT b8   input_key_pressed(u32 key);
CEXPORT b8   input_key_down(u32 key);
CEXPORT b8   input_key_up(u32 key);
CEXPORT void input_mouse_position_get(i32 *x, i32 *y);
CEXPORT void input_mouse_wheel_get(i32 *delta);

// Module Interface

typedef struct CModuleAPI
{
    void (*startup)(void);
    void (*update)(f32 dt);
    void (*shutdown)(void);
} CModuleAPI;

CEXPORT void module_startup_stub(void);
CEXPORT void module_update_stub(f32 dt);
CEXPORT void module_shutdown_stub(void);

// Layer Interface

typedef struct CLayer
{
    b8         is_valid;
    CModuleAPI api;
} CLayer;

CEXPORT void layer_main(CLayer *layer);

// Library Interface

typedef struct CLibrary
{
    b8         is_valid;
    void      *handle;
    CModuleAPI api;
} CLibrary;

CEXPORT CLibrary library_load(const char *path);
CEXPORT void     library_unload(CLibrary *library);
CEXPORT void    *library_load_function(CLibrary *library, const char *name);

// Logger Interface

CEXPORT void log_info(const char *format, ...);
CEXPORT void log_debug(const char *format, ...);
CEXPORT void log_warning(const char *format, ...);
CEXPORT void log_error(const char *format, ...);

// Math Interface

#define COLOR_RED         v4(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_RED_DARK    v4(0.5f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN       v4(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_GREEN_DARK  v4(0.0f, 0.5f, 0.0f, 1.0f)
#define COLOR_BLUE        v4(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_BLUE_DARK   v4(0.0f, 0.0f, 0.5f, 1.0f)
#define COLOR_PINK        v4(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_PINK_DARK   v4(0.5f, 0.0f, 0.5f, 1.0f)
#define COLOR_YELLOW      v4(1.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_YELLOW_DARK v4(0.5f, 0.5f, 0.0f, 1.0f)
#define COLOR_CYAN        v4(0.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_CYAN_DARK   v4(0.0f, 0.5f, 0.5f, 1.0f)
#define COLOR_WHITE       v4(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_BLACK       v4(0.0f, 0.0f, 0.0f, 1.0f)

CEXPORT f32 m_radiansf(f32 degree);
CEXPORT f32 m_degreesf(f32 radian);
CEXPORT f64 m_radians(f64 degree);
CEXPORT f64 m_degrees(f64 radian);

// Memory Interface

#ifndef NDEBUG
#define MemoryAlloc(type, size)                                               \
    (type *)_debug_memory_alloc(size * sizeof(type), __FILE__, __LINE__)
#define MemoryFree(memory) _debug_memory_free(memory, __FILE__, __LINE__)
#define MemoryZero(memory, type, size)                                        \
    _debug_memory_zero(memory, size * sizeof(type), __FILE__, __LINE__)
#define MemoryCopy(dest, src, type, size)                                     \
    _debug_memory_copy(dest, src, size * sizeof(type), __FILE__, __LINE__)
#else
#define MemoryAlloc(type, size)        (type *)malloc(size * sizeof(type))
#define MemoryFree(memory)             free(memory)
#define MemoryZero(memory, type, size) memset(memory, 0, size * sizeof(type))
#define MemoryCopy(dest, src, type, size)                                     \
    memcpy(dest, src, size * sizeof(type))
#endif

#define MemoryAllocArray(type, size)        MemoryAlloc(type, size)
#define MemoryAllocStruct(type)             MemoryAlloc(type, 1)
#define MemoryZeroArray(memory, type, size) MemoryZero(memory, type, size)
#define MemoryZeroStruct(memory, type)      MemoryZero(memory, type, 1)
#define MemoryCopyArray(dest, src, type, size)                                \
    MemoryCopy(dest, src, type, size)
#define MemoryCopyStruct(dest, src, type) MemoryCopy(dest, src, type, 1)

typedef struct CMemoryArena     CMemoryArena;
typedef struct CMemoryArenaTemp CMemoryArenaTemp;

CEXPORT CMemoryArena *arena_create(u64 size);
CEXPORT void          arena_destroy(CMemoryArena *arena);
CEXPORT void         *arena_push(CMemoryArena *arena, u64 size);
CEXPORT void         *arena_push_zero(CMemoryArena *arena, u64 size);
CEXPORT void         *arena_pop(CMemoryArena *arena, u64 size);
CEXPORT void          arena_clear(CMemoryArena *arena);
CEXPORT u64           arena_offset_get(CMemoryArena *arena);

CEXPORT CMemoryArenaTemp arena_temp_begin(CMemoryArena *arena);
CEXPORT void             arena_temp_end(CMemoryArenaTemp temp);
CEXPORT CMemoryArenaTemp arena_temp_scratch_get(CMemoryArena *arena);

#define PushArray(arena, type, count)                                         \
    (type *)arena_push(arena, count * sizeof(type))
#define PushArrayZero(arena, type, count)                                     \
    (type *)arena_push_zero(arena, count * sizeof(type))
#define PushStruct(arena, type)     PushArray(arena, 1)
#define PushStructZero(arena, type) PushArrayZero(arena, 1)
#define PopArray(arena, type, count)                                          \
    (type *)arena_pop(arena, count * sizeof(type))
#define PopStruct(arena, type) PopArray(arena, 1)

// Module Interface

typedef struct CMouduleMemory
{
    b8            is_initialized;
    CMemoryArena *permanent_storage;
    CMemoryArena *transient_storage;
} CMouduleMemory;

#endif // CORE_H
