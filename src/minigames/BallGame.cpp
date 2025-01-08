// BallGame.cpp
#include "BallGame.h"

using namespace std;

// BallGame constructor
BallGame::BallGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title),
      window_width(width),
      window_height(height),
      score(0), // Inicjalizacja punktów
      gameOver(false), // Inicjalizacja stanu gry
      //gameComplete(false), // Inicjalizacja flagi zakończenia gry
      maxScore(3),
      maxAttempts(20)
{
    // Initialize ball properties based on window size
    ball_radius = window_width * 0.05f;
    ball_x = window_width * 0.05f;
    ball_y = window_height / 2;
    ball_speed = 6;

    // Initialize rectangles' positions and speeds relative to window size
    RectangleEntity rect1;
    rect1.x = window_width / 2;
    rect1.y = window_height / 2 - (window_height * 0.1f);
    rect1.speed_y = window_height * 0.025f; // Bez cast na int

    RectangleEntity rect2;
    rect2.x = window_width / 2 - (window_width * 0.2f);
    rect2.y = window_height / 2 - (window_height * 0.15f);
    rect2.speed_y = -window_height * 0.03f; // Bez cast na int i z minusem

    RectangleEntity rect3;
    rect3.x = window_width / 2 + (window_width * 0.2f);
    rect3.y = window_height / 2 + (window_height * 0.1f); // Zmieniono 0.15f na 0.1f
    rect3.speed_y = window_height * 0.0225f; // Bez cast na int

    // Dodanie prostokątów do listy
    rectangles.push_back(rect1);
    rectangles.push_back(rect2);
    rectangles.push_back(rect3);

    attempts = maxAttempts;
}

// Reset pozycji piłki
void BallGame::BallReset(){
    ball_x = window_width * 0.05f;
    ball_y = window_height / 2;
}

// Funkcja kończąca grę
void BallGame::GameOver(){
    // Obliczenie pozycji w zależności od window.x i window.y
    float centerX = window.x + window_width / 2;
    float centerY = window.y + window_height / 2;

    string gameOverText = "Game Over";
    string scoreText = "Score: " + to_string(score);
    string attemptsText = "Attempts Left: " + to_string(attempts);
    string restartText = "Press 'R' to Restart";

    // Rysowanie tekstu "Game Over"
    DrawText(gameOverText.c_str(), 
             centerX - MeasureText(gameOverText.c_str(), 40) / 2, 
             centerY - 80, 
             40, 
             RED);
    
    // Rysowanie wyniku
    DrawText(scoreText.c_str(), 
             centerX - MeasureText(scoreText.c_str(), 30) / 2, 
             centerY - 20, 
             30, 
             WHITE);
    
    // Rysowanie liczby pozostałych prób
    DrawText(attemptsText.c_str(), 
             centerX - MeasureText(attemptsText.c_str(), 30) / 2, 
             centerY + 30, 
             30, 
             WHITE);
    
    // Rysowanie instrukcji restartu
    DrawText(restartText.c_str(), 
             centerX - MeasureText(restartText.c_str(), 20) / 2, 
             centerY + 80, 
             20, 
             WHITE);
}

// Rysowanie piłki
void BallGame::DrawBall(){
    DrawCircle(window.x + ball_x, window.y + ball_y, ball_radius, PINK);
}

// Rysowanie prostokątów
void BallGame::DrawRectangles(){
    float rect_width = window_width * 0.05f;
    float rect_height = window_height * 0.35f; // Zmniejszenie wysokości z 0.4f na 0.35f
    for(auto &rect : rectangles){
        DrawRectangle(window.x + rect.x, window.y + rect.y, rect_width, rect_height, BLUE);
    }
}

// Aktualizacja pozycji prostokątów
void BallGame::UpdateRectangles(){
    float rect_height = window_height * 0.35f; // Zmniejszona wysokość
    for(auto &rect : rectangles){
        rect.y += rect.speed_y;

        // Sprawdzenie granic okna
        if(rect.y + rect_height >= window_height){
            rect.y = window_height - rect_height;
            rect.speed_y *= -1;
        }
        else if(rect.y <= 0){
            rect.y = 0;
            rect.speed_y *= -1;
        }
    }
}

// Obsługa kolizji piłki z prostokątami
void BallGame::HandleCollision(){
    float rect_width = window_width * 0.05f;
    float rect_height = window_height * 0.35f; // Zmniejszona wysokość
    for(auto &rect : rectangles){
        if(CheckCollisionCircleRec(Vector2{ball_x + window.x, ball_y + window.y}, ball_radius,
                                  Rectangle{rect.x + window.x, rect.y + window.y, rect_width, rect_height})){
            attempts -= 1; // Odejmowanie próby na kolizję
            BallReset(); // Reset pozycji piłki bez zmiany punktów
            if(attempts <= 0 && score < maxScore){
                gameOver = true; // Zakończenie gry, jeśli brak prób
            }
            break;
        }
    }
}

// Sprawdzenie, czy piłka osiągnęła metę
void BallGame::CheckScore(){
    if(ball_x + ball_radius >= window_width){
        score += 1;
        attempts -= 1; // Odejmowanie próby po osiągnięciu mety
        if(score >= maxScore){
            gameOver = true; // Zakończenie gry
            if(attempts > 0){
                gameComplete = true; // Ustawienie flagi zakończenia gry jako kompletnej
            }
        } else if(attempts <= 0){
            gameLost = true;
        } else {
            BallReset(); // Reset pozycji piłki po zdobyciu punktu
            IncreaseDifficulty(); // Zwiększenie trudności po zdobyciu punktu
        }
    }
}

// Zwiększenie trudności gry
void BallGame::IncreaseDifficulty(){
    // Delikatne zwiększenie prędkości prostokątów
    for(auto &rect : rectangles){
        rect.speed_y *= 1.02f; // Zwiększenie prędkości o 2%
    }
}

// Resetowanie całej gry
void BallGame::ResetGame(){
    score = 0;
    attempts = maxAttempts;
    gameOver = false;
    gameComplete = false; // Resetowanie flagi zakończenia gry
    BallReset();
    // Resetowanie prędkości prostokątów do początkowych wartości
    rectangles.clear();
    RectangleEntity rect1;
    rect1.x = window_width / 2;
    rect1.y = window_height / 2 - (window_height * 0.1f);
    rect1.speed_y = window_height * 0.025f;

    RectangleEntity rect2;
    rect2.x = window_width / 2 - (window_width * 0.2f);
    rect2.y = window_height / 2 - (window_height * 0.15f);
    rect2.speed_y = -window_height * 0.03f;

    RectangleEntity rect3;
    rect3.x = window_width / 2 + (window_width * 0.2f);
    rect3.y = window_height / 2 + (window_height * 0.1f);
    rect3.speed_y = window_height * 0.0225f;

    rectangles.push_back(rect1);
    rectangles.push_back(rect2);
    rectangles.push_back(rect3);
}

// Główna funkcja aktualizująca grę
void BallGame::Update(){
    if(gameOver){
        if(IsKeyPressed(KEY_R)){
            // Resetowanie gry
            ResetGame();
        }
        return; // Pomijanie dalszej aktualizacji, gdy gra jest zakończona
    }

    // Obsługa sterowania piłką
    if(IsKeyDown(KEY_RIGHT)){
        ball_x += ball_speed;
    }
    if(IsKeyDown(KEY_LEFT)){
        ball_x -= ball_speed;
    }
    if(IsKeyDown(KEY_DOWN)){
        ball_y += ball_speed;
    }
    if(IsKeyDown(KEY_UP)){
        ball_y -= ball_speed;
    }

    // Zapewnienie, że piłka pozostaje w granicach okna
    if(ball_x - ball_radius < 0){
        ball_x = ball_radius;
    }

    // Sprawdzenie, czy piłka osiągnęła metę
    CheckScore();

    if(ball_y - ball_radius < 0){
        ball_y = ball_radius;
    }
    if(ball_y + ball_radius > window_height){
        ball_y = window_height - ball_radius;
    }

    // Aktualizacja prostokątów
    UpdateRectangles();

    // Obsługa kolizji z prostokątami
    HandleCollision();
}

// Główna funkcja rysująca grę
void BallGame::Draw(){
    // Rysowanie prostokątów
    DrawRectangles();

    // Rysowanie piłki
    DrawBall();

    // Rysowanie punktacji na górnym pasku, na środku
    string scoreText = "Score: " + to_string(score);
    int fontSize = 20;
    int textWidth = MeasureText(scoreText.c_str(), fontSize);
    float scoreX = window.x + (window_width / 2) - (textWidth / 2);
    float scoreY = window.y + 10; // 10 pikseli od górnej krawędzi
    DrawText(scoreText.c_str(), scoreX, scoreY, fontSize, WHITE);

    // Rysowanie liczby pozostałych prób na dole okna, na środku
    string attemptsText = "Attempts Left: " + to_string(attempts);
    textWidth = MeasureText(attemptsText.c_str(), fontSize);
    float attemptsX = window.x + (window_width / 2) - (textWidth / 2);
    float attemptsY = window.y + window_height - 30; // 30 pikseli od dolnej krawędzi
    DrawText(attemptsText.c_str(), attemptsX, attemptsY, fontSize, WHITE);

    // Jeśli osiągnięto maksymalną punktację lub wyczerpano próby, zakończ grę
    if(gameOver){
        GameOver();
    }

    // Opcjonalne: Wyświetlenie komunikatu, jeśli gra została ukończona
    if(gameComplete){
        float centerX = window.x + window_width / 2;
        float centerY = window.y + window_height / 2;
        string completeText = "Game Completed Successfully!";
        DrawText(completeText.c_str(),
                 centerX - MeasureText(completeText.c_str(), 30) / 2,
                 centerY,
                 30,
                 GREEN);
    }
}
