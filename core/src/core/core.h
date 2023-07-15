#ifndef CORE_H
#define CORE_H

#include "core/types.h"

// Core Interface

API void core_startup(void);
API void core_shutdown(void);
API void core_sleep(u32 ms);
API u64  core_perf_counter(void);
API u64  core_perf_frequency(void);

// Container Interface

// String

typedef struct String8
{
    u8 *str;
    u64 size;
} String8;

API String8 str8(const char *c);
API char   *str8_c(const String8 string);
API b8      str8_eq(const String8 left, const String8 right);

// Vector2F

typedef union
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
} V2F;

API V2F v2f(f32 x, f32 y);
API V2F v2f_add(V2F left, V2F right);
API V2F v2f_addf(V2F left, f32 right);
API V2F v2f_sub(V2F left, V2F right);
API V2F v2f_subf(V2F left, f32 right);
API V2F v2f_mul(V2F left, V2F right);
API V2F v2f_mulf(V2F left, f32 right);
API V2F v2f_div(V2F left, V2F right);
API V2F v2f_divf(V2F left, f32 right);
API f32 v2f_dot(V2F left, V2F right);
API b32 v2f_eq(V2F left, V2F right);
API V2F v2f_norm(V2F v);
API f32 v2f_sqrt_len(V2F v);
API f32 v2f_len(V2F v);
API V2F v2f_lerp(V2F left, V2F right, f32 time);

// Vector3F

typedef union
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
        V2F xy;
        f32 _ignored0;
    };

    struct
    {
        f32 _ignored1;
        V2F yz;
    };

    struct
    {
        V2F uv;
        f32 _ignored2;
    };

    struct
    {
        f32 _ignored3;
        V2F vw;
    };

    f32 elements[3];
} V3F;

API V3F v3f(f32 x, f32 y, f32 z);
API V3F v3f_add(V3F left, V3F right);
API V3F v3f_sub(V3F left, V3F right);
API V3F v3f_mul(V3F left, V3F right);
API V3F v3f_mulf(V3F left, f32 right);
API V3F v3f_div(V3F left, V3F right);
API V3F v3f_divf(V3F left, f32 right);
API f32 v3f_dot(V3F left, V3F right);
API b32 v3f_eq(V3F left, V3F right);
API V3F v3f_norm(V3F v);
API f32 v3f_sqrt_len(V3F v);
API f32 v3f_len(V3F v);
API V3F v3f_lerp(V3F left, V3F right, f32 time);

// Vector4F

typedef union
{
    struct
    {
        union
        {
            V3F xyz;
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
            V3F rgb;
            struct
            {
                f32 r, g, b;
            };
        };

        f32 a;
    };

    struct
    {
        V2F xy;
        f32 _ignored0;
        f32 _ignored1;
    };

    struct
    {
        f32 _ignored2;
        V2F yz;
        f32 _ignored3;
    };

    struct
    {
        f32 _ignored4;
        f32 _ignored5;
        V2F zw;
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
} V4F;

API V4F v4f(f32 x, f32 y, f32 z, f32 w);
API V4F v4f_add(V4F left, V4F right);
API V4F v4f_sub(V4F left, V4F right);
API V4F v4f_mul(V4F left, V4F right);
API V4F v4f_mulf(V4F left, f32 right);
API V4F v4f_div(V4F left, V4F right);
API V4F v4f_divf(V4F left, f32 right);
API f32 v4f_dot(V4F left, V4F right);
API b32 v4f_eq(V4F left, V4F right);
API V4F v4f_norm(V4F v);
API f32 v4f_sqrt_len(V4F v);
API f32 v4f_len(V4F v);
API V4F v4f_lerp(V4F left, V4F right, f32 time);

// Asset Interface

typedef struct IImage      IImage;
typedef struct IAssetState IAssetState;

API void    asset_init(void);
API void    asset_destroy(void);
API void   *asset_file_rw_data_load(const char *file_path);
API IImage *asset_image_load(const char *file_path);
API void    asset_image_unload(IImage *image);
API void    asset_image_size_get(IImage *image, i16 *width, i16 *height);

// Audio Interface

typedef struct AudioState AudioState;

API void        audio_init(void);
API AudioState *audio_load(const char *file_path);
API void        audio_unload(AudioState *audio_state);
API void        audio_play(AudioState *audio_state, bool loop);
API void        audio_stop(AudioState *audio_state);

// Debug Interface

typedef struct DebugState DebugState;

API void debug_profiler_init(void);
API void debug_profiler_destroy(void);
API void debug_profiler_handle(void);

void *_debug_profiler_timed_block_begin(const char *func_name);
void  _debug_profiler_timed_block_end(void *counter_ptr, u64 cycle_count);

#define PROFILER_BEGIN(NAME)                                                  \
    void *current_counter_##NAME = _debug_profiler_timed_block_begin(#NAME);  \
    u64   start_##NAME = forge_perf_counter();

#define PROFILER_END(NAME)                                                    \
    u64 end_##NAME = forge_perf_counter();                                    \
    _debug_profiler_timed_block_end(current_counter_##NAME,                   \
                                    end_##NAME - start_##NAME);

// Window Interface

typedef struct WindowState WindowState;

API WindowState *window_open(const char *title, i32 xpos, i32 ypos, i32 width,
                             i32 height);
API void         window_close(WindowState *window);

// Event Interface

typedef enum EventCode
{
    EventCode_AppQuit,
    EventCode_KeyPressed,
    EventCode_KeyReleased,
    EventCode_ButtonPressed,
    EventCode_ButtonReleased,
    EventCode_MouseMotion,
    EventCode_MouseWheel,
    EventCode_WindowResized,
    EventCode_Count,
} EventCode;

typedef struct EventCtx
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
} EventCtx;

typedef b8 (*event_fn_on_event)(u16 code, void *sender, void *listener_fn,
                                EventCtx data);

API b8 event_init(void);
API b8 event_destroy(void);
API b8 event_register(u16 code, void *listener, event_fn_on_event on_event);
API b8 event_unregister(u16 code, void *listener, event_fn_on_event on_event);
API b8 event_fire(u16 code, void *sender, EventCtx context);

// Input Interface

typedef enum MouseButton
{
    MouseButton_Left,
    MouseButton_Middle,
    MouseButton_Right,
    MouseButton_Count,
} MouseButton;

typedef enum KeyCode
{
    KeyCode_A,
    KeyCode_D,
    KeyCode_W,
    KeyCode_S,
    KeyCode_Q,
    KeyCode_E,
    KeyCode_Escape,
    KeyCode_Count,
} KeyCode;

typedef struct KeyboardState
{
    b8 keys[KeyCode_Count];
} KeyboardState;

typedef struct MouseState
{
    i16 x, y;
    i16 wheel;
    b8  buttons[MouseButton_Count];
} MouseState;

typedef struct InputState
{
    KeyboardState keyboard_current;
    KeyboardState keyboard_previous;

    MouseState mouse_current;
    MouseState mouse_previous;
} InputState;

API void input_startup(void);
API void input_shutdown(void);

API void input_button_process(MouseButton button, b8 state);
API void input_key_process(KeyCode key, b8 state);
API void input_mouse_motion_process(i16 x, i16 y);
API void input_mouse_scroll_process(i16 z_delta);

API void input_update(void);
API b32  input_button_pressed(i16 button);
API b32  input_button_down(i16 button);
API b32  input_button_up(i16 button);
API b32  input_key_pressed(i16 key);
API b32  input_key_down(i16 key);
API b32  input_key_up(i16 key);
API void input_mouse_position_get(i16 *x, i16 *y);
API void input_mouse_wheel_get(i16 *z_delta);

// Library Interface

typedef struct Library Library;

API Library *library_load(char *path);
API Library *library_unload(Library *lib);

// Logger Interface

API void log_info(const char *format, ...);
API void log_warning(const char *format, ...);
API void log_error(const char *format, ...);

// Math Interface

#define COLOR_RED v4f(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_RED_DARK v4f(0.5f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN v4f(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_GREEN_DARK v4f(0.0f, 0.5f, 0.0f, 1.0f)
#define COLOR_BLUE v4f(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_BLUE_DARK v4f(0.0f, 0.0f, 0.5f, 1.0f)
#define COLOR_PINK v4f(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_PINK_DARK v4f(0.5f, 0.0f, 0.5f, 1.0f)
#define COLOR_YELLOW v4f(1.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_YELLOW_DARK v4f(0.5f, 0.5f, 0.0f, 1.0f)
#define COLOR_CYAN v4f(0.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_CYAN_DARK v4f(0.0f, 0.5f, 0.5f, 1.0f)
#define COLOR_WHITE v4f(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_BLACK v4f(0.0f, 0.0f, 0.0f, 1.0f)

API f32 m_radiansf(f32 degree);
API f32 m_degreesf(f32 radian);
API f64 m_radians(f64 degree);
API f64 m_degrees(f64 radian);

// Memory Interface

typedef struct MemoryArena     MemoryArena;
typedef struct MemoryArenaTemp MemoryArenaTemp;

API MemoryArena *arena_create(u64 size);
API void         arena_destroy(MemoryArena *arena);
API void        *arena_push(MemoryArena *arena, u64 size);
API void        *arena_push_zero(MemoryArena *arena, u64 size);
API void        *arena_pop(MemoryArena *arena, u64 size);
API void         arena_clear(MemoryArena *arena);
API u64          arena_offset_get(MemoryArena *arena);

API MemoryArenaTemp arena_temp_begin(MemoryArena *arena);
API void            arena_temp_end(MemoryArenaTemp temp);
API MemoryArenaTemp arena_temp_scratch_get(MemoryArena *arena);

#endif // CORE_H
