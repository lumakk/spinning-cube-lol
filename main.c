#include "raylib.h"
#include "raymath.h"

int main(void) {

  // INITIALIZE WINDOW 
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  int screenWidth = 800;
  int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "spinning cube");

  // INITIALIZE CAMERA 
  Camera camera = { 0 };
  camera.position = (Vector3){0.0f, 3.0f, 3.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.target = (Vector3) {0.0f, 0.0f, 0.0f};

  
  // CUBE TEXTURE 
  Model model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
  Image img = LoadImage("./assets/cube.png");
  Texture2D texture = LoadTextureFromImage(img);
  UnloadImage(img);

  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  float rotation = 0.0f;

  
  SetTargetFPS(60); // Set FPS 
  
  // MAIN GAME LOOP 
  while (!WindowShouldClose()) {
    // CUBE ROTATION 
    rotation += 1.0f; 

    // ZOOM 
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      Vector3 view = Vector3Subtract(camera.target, camera.position);
      Vector3 move = Vector3Scale(Vector3Normalize(view), wheel * 2.0f);
      camera.position = Vector3Add(camera.position, move);
    }

    // ORBIT 
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 delta = GetMouseDelta();
      float sensitivity = 0.005f;

      Vector3  view = Vector3Subtract(camera.position, camera.target);
      view = Vector3RotateByAxisAngle(view, (Vector3) {0.0f, 1.0f, 0.0f}, -delta.x * sensitivity);
      Vector3 right = Vector3CrossProduct(Vector3Normalize(view), (Vector3){0.0f, 1.0f, 0.0f});
      view = Vector3RotateByAxisAngle(view, right, -delta.y * sensitivity);
      
      camera.position = Vector3Add(camera.target, view);
    }
    
    // DRAW 
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(camera);
        DrawModelEx(model, (Vector3) {0.0f, 0.0f, 0.0f}, (Vector3) {0.5f, 1.0f, 0.0f}, rotation, (Vector3) {1.0f, 1.0f, 1.0f},  WHITE);
        DrawGrid(10, 1.0f);
      EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();

  }

  // DE-INITIALIZE
  UnloadTexture(texture);
  UnloadModel(model);

  CloseWindow();

  return 0;
}
