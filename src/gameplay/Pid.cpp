#include "Pid.h"
#include "../headers/globals.h"
#include "gameplay_vars.h"

// Constructor to initialize PID menu properties
Pid::Pid() {
    pidMenu = {screen.x + 900, screen.y + 97, 249, 540};
    idle = true;
    displayEnemyIpFrames = 0;
    animationTimer = 0;
}

// Render the PID menu
void Pid::RenderIdle() {
    DrawRectangleRec(pidMenu, BLACK);
    DrawTextC("NO", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) - 50, 40, primaryColor);
    DrawTextC("PROCESS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
    DrawTextC("ACTIVE", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) + 50, 40, primaryColor);
}

// Added animatePortscanResult function
void Pid::PortscanRender() {
    const int animationDuration = 300; // Frames for the animation

    if(animationTimer < animationDuration){
        animationTimer++;
        // Animate random number generation
        int randomNumber = rand() % 65535;
        DrawTextC(std::to_string(randomNumber).c_str(), pidMenu.x + 50, pidMenu.y + (pidMenu.height/2) - 10, 40, primaryColor);
    }

    if(gameplayManager.timer.countdownFrames < 300){
        // Draw black rectangle to cover the random number
        DrawRectangle(pidMenu.x + 50, pidMenu.y + (pidMenu.height/2) - 10, 200, 100, BLACK);
        
        if(gameplayManager.portscanResult == 0){
            DrawTextC("Failure", pidMenu.x + 50, pidMenu.y + (pidMenu.height/2) - 10, 40, RED);
        }
        else{
            DrawTextC(std::to_string(gameplayManager.portscanResult).c_str(), pidMenu.x + 50, pidMenu.y + (pidMenu.height/2) - 10, 40, GREEN);
        }
    }

    DrawTextC("PROCESS: PORT", pidMenu.x + 10, pidMenu.y + 10, 20, primaryColor);
    DrawTextC("SCAN //", pidMenu.x + 10, pidMenu.y + 30, 20, primaryColor);
    std::string timeLeft = "EST. T.LEFT: " + std::to_string(gameplayManager.timer.countdownFrames / 60);
    DrawTextC(timeLeft.c_str(), pidMenu.x + 10, pidMenu.y + 50, 20, primaryColor);
}

void Pid::Render() {
    // Debug: Check timer status
    if(!isCounting && displayEnemyIpFrames == 0) {
        RenderIdle();
    } else {
        switch(pidState) {
            case B_DRAIN: {
                b_DrainRender();
                if(gameplayManager.timer.countdownFrames == 1){
                    cmdInterpreter.outputLine("Netscan: Brute Force Drain complete.");
                    cmdInterpreter.outputLine("Netscan: Remaining IP: " + gameplayManager.enemyIp);
                    cmdInterpreter.outputLine("Netscan: Enemy Ip Saved.");
                    isEnemyIpKnown = true;
                }
                break;
            }
            case S_DRAIN:
                s_DrainRender();
                if(gameplayManager.timer.countdownFrames == 1){
                    cmdInterpreter.outputLine("Netscan: Silent Drain complete.");
                    cmdInterpreter.outputLine("Netscan: Remaining IP's: " + std::to_string(gameplayManager.selectedIpPool.size()));
                }
                break;
            case MAIL:
                MailRender();
                break;
            case DDOS:
                DdosRender();
                break;
            case ADD_BOTNET:
                DrawTextC("ADD BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case ATK_BOTNET:
                DrawTextC("ATTACK BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case PORTSCAN:
                animationTimer = 0; // Reset the timer
                PortscanRender();
                break;
            default:
                break;
        }
    }
    DrawRectangleLinesEx(pidMenu, 2, primaryColor);
}

// Define a struct for animated IPs
struct AnimatedIP {
    std::string ip;
    float x;
    float y;
    float alpha;
    float fadeSpeed; // New attribute for individual fade speed
};

void Pid::b_DrainRender() {
// Initialize animation variables
    static std::vector<AnimatedIP> animatedIPs;
    static bool animationStarted = false;
    static int enemyIpAlpha = 0; // Make enemyIpAlpha retain its value across calls

    if (!animationStarted) {
        // Populate animatedIPs with random IPs from ipPool
        for(int i = 0; i < 100; ++i){ // Start with 100 IPs for longer fading
            AnimatedIP newIP;
            newIP.ip = gameplayManager.ipPool[rand() % 100]; // Random IP

            // Random x and y within pidMenu boundaries
            newIP.x = pidMenu.x + 2 + rand() % (int)(pidMenu.width - (MeasureTextEx(pixeled, newIP.ip.c_str(), 20, 1).x) - 15);
            newIP.y = pidMenu.y + 80 + rand() % (int)(pidMenu.height - 100);

            newIP.alpha = 255.0f; // Fully opaque
            newIP.fadeSpeed = 255.0f / (30.0f * 60.0f); // Fade over 30 seconds (assuming 60 FPS)
            animatedIPs.push_back(newIP);
        }
        animationStarted = true;
    }

    // Update and render animated IPs
    for(auto it = animatedIPs.begin(); it != animatedIPs.end(); ) {
        it->alpha -= it->fadeSpeed; // Fade out at individual speed

        // Draw IP text within pidMenu
        DrawTextC(it->ip.c_str(), 
                    ShakeXY((int)it->x, 2), 
                    ShakeXY((int)it->y, 2), 
                    20, 
                    (Color){primaryColor.r, primaryColor.g, primaryColor.b, (unsigned char)(std::max(0.0f, it->alpha))});

        // Remove if fully faded
        if(it->alpha <= 0){
            it = animatedIPs.erase(it);
        } else {
            ++it;
        }
    }

    if(gameplayManager.timer.countdownFrames <= 200){
        if(enemyIpAlpha < 255){
            enemyIpAlpha ++; // Increment alpha to gradually increase visibility
            if(enemyIpAlpha > 255){
                enemyIpAlpha = 255; // Cap alpha at 255
            }
        }
        // Draw enemy IP text centrally with increasing alpha
        DrawTextC(gameplayManager.enemyIp.c_str(), 
                 pidMenu.x + (pidMenu.width - MeasureText(gameplayManager.enemyIp.c_str(), 20)) / 2, 
                 pidMenu.y + (pidMenu.height / 2) - 10, 
                 20, 
                 (Color){primaryColor.r, primaryColor.g, primaryColor.b, (unsigned char)enemyIpAlpha});
    }


    // Draw additional texts
    DrawTextC("PROCESS: DRAIN //", pidMenu.x + 10, pidMenu.y + 10, 20, primaryColor);
    DrawTextC("--BRUTEFORCE", pidMenu.x + 10, pidMenu.y + 30, 20, primaryColor);

    // Fix the warning by correctly converting to char*
    std::string timeLeft = "EST. T.LEFT: " + std::to_string(gameplayManager.timer.countdownFrames / 60);
    DrawTextC(timeLeft.c_str(), pidMenu.x + 10, pidMenu.y + 50, 20, primaryColor);
}

void Pid::s_DrainRender() {
    // Initialize animation variables
    static std::vector<AnimatedIP> animatedIPs;
    static bool animationStarted = false;
    static int framesPerIp = 0;

    if (!animationStarted) {
        // Populate animatedIPs with IPs from the old_selectedIpPool
        for(const auto& ip : gameplayManager.old_selectedIpPool) {
            AnimatedIP newIP;
            newIP.ip = ip;

            // Random x and y within pidMenu boundaries
            newIP.x = pidMenu.x + 2 + rand() % (int)(pidMenu.width - (MeasureTextEx(pixeled, newIP.ip.c_str(), 20, 1).x) - 15);
            newIP.y = pidMenu.y + 80 + rand() % (int)(pidMenu.height - 100);

            newIP.alpha = 255.0f; // Fully opaque
            newIP.fadeSpeed = 255.0f / (5.0f * 60.0f); // Fade over 5 seconds (assuming 60 FPS)
            animatedIPs.push_back(newIP);
        }
        framesPerIp = 5 * 60 / animatedIPs.size(); // Calculate frames per IP for 5 seconds
        animationStarted = true;
    }

    // Update and render animated IPs
    int currentFrame = gameplayManager.timer.countdownFrames;
    int ipIndex = (5 * 60 - currentFrame) / framesPerIp;

    for(int i = 0; i < animatedIPs.size(); ++i) {
        if (gameplayManager.selectedIpPool.find(animatedIPs[i].ip) == gameplayManager.selectedIpPool.end()) {
            // Fade out IPs not in selectedIpPool
            animatedIPs[i].alpha -= animatedIPs[i].fadeSpeed;
            if(animatedIPs[i].alpha < 0){
                animatedIPs[i].alpha = 0;
            }
        } else {
            animatedIPs[i].alpha = 255.0f; // Ensure selected IPs remain fully opaque
        }

        // Draw IP text within pidMenu
        DrawTextC(animatedIPs[i].ip.c_str(), 
                  ShakeXY(static_cast<int>(animatedIPs[i].x), 2), 
                  ShakeXY(static_cast<int>(animatedIPs[i].y), 2), 
                  20, 
                  (Color){primaryColor.r, primaryColor.g, primaryColor.b, static_cast<unsigned char>(std::max(0.0f, animatedIPs[i].alpha))});
    }

    // Draw additional texts
    DrawTextC("PROCESS: DRAIN //", pidMenu.x + 10, pidMenu.y + 10, 20, primaryColor);
    DrawTextC("--SILENT", pidMenu.x + 10, pidMenu.y + 30, 20, primaryColor);

    // Fix the warning by correctly converting to char*
    std::string timeLeft = "EST. T.LEFT: " + std::to_string(gameplayManager.timer.countdownFrames / 60);
    DrawTextC(timeLeft.c_str(), pidMenu.x + 10, pidMenu.y + 50, 20, primaryColor);
}

struct FallingRect {
    float x;
    float y;
    float width;
    float height;
    float speed;
    float alpha; // Added alpha for transparency
};

// Define a struct for loading stripes
struct LoadingStripe {
    float x;
    float y;
    float width;
    float height;
    float progress; // Current progress (0.0 to 1.0)
    float speed;    // Speed of progress per frame
    bool linkedToTimer; // If true, progress is tied to countdownFrames
};

void Pid::DdosRender() {
    static std::vector<FallingRect> fallingRects;
    static std::vector<LoadingStripe> loadingStripes;
    static bool stripesInitialized = false;
    static float frames;

    // Initialize loading stripes once
    if (!stripesInitialized) {
        int numberOfStripes = 4;
        float stripeHeight = 20.0f;
        float spacing = 10.0f;
        float startY = pidMenu.y + 90.0f; // Starting Y position for the first stripe
        frames = gameplayManager.timer.countdownFrames;
        
        for(int i = 0; i < numberOfStripes; ++i){
            LoadingStripe stripe;
            stripe.x = pidMenu.x + 20.0f; // Starting X position
            stripe.y = startY + i * (stripeHeight + spacing); // Stacked vertically
            stripe.width = pidMenu.width - 40.0f; // Width minus padding
            stripe.height = stripeHeight;
            stripe.progress = 0.0f;
            stripe.speed = 0.5f + static_cast<float>(i) * 0.2f; // Different speeds
            stripe.linkedToTimer = (i == 0); // First stripe linked to timer
            loadingStripes.push_back(stripe);
        }
        stripesInitialized = true;
    }

    // Update loading stripes
    for(auto &stripe : loadingStripes){
        if(stripe.linkedToTimer){
            if(gameplayManager.timer.countdownFrames >= 0){
                // Calculate progress based on countdownFrames
                stripe.progress = 1.0f - static_cast<float>(gameplayManager.timer.countdownFrames) / frames; // Assuming 20000 frames
                if(stripe.progress > 1.0f){
                    stripe.progress = 1.0f;
                }
                else if(stripe.progress < 0.0f){
                    stripe.progress = 0.0f;
                }
            }
            else{
                stripe.progress = 1.0f; // Complete loading
            }
        }
        else{
            // Update progress based on speed
            stripe.progress += stripe.speed / static_cast<float>(60); // Assuming 60 FPS
            if(stripe.progress > 1.0f){
                stripe.progress = 0.0f; // Reset to loop the loading
            }
        }
    }

    // Draw loading stripes
    for(const auto &stripe : loadingStripes){
        // Draw the background of the stripe
        DrawRectangle(stripe.x, stripe.y, stripe.width, stripe.height, BLACK);
        // Draw the filled part of the stripe
        DrawRectangle(stripe.x, stripe.y, stripe.width * stripe.progress, stripe.height, primaryColor);
    }

    // Update and draw falling rectangles
    for(auto it = fallingRects.begin(); it != fallingRects.end(); ){
        it->y += it->speed;
        // Apply alpha to primaryColor
        Color rectColor = primaryColor;
        rectColor.a = static_cast<unsigned char>(std::clamp(it->alpha, 0.0f, 255.0f));
        DrawRectangle(it->x, it->y, it->width, it->height, rectColor);
        
        // Optionally decrease alpha as the rectangle falls
        it->alpha -= 1.0f; // Decrease alpha for fading effect

        // Check if rectangle has reached the bottom
        if(it->y + it->height >= pidMenu.y + pidMenu.height){
            it->y = pidMenu.y + pidMenu.height - it->height; // Clamp to bottom
            it = fallingRects.erase(it); // Remove the rectangle
        }
        else if(it->alpha <= 0){
            it = fallingRects.erase(it);
        }
        else{
            ++it;
        }
    }

    // Generate new falling rectangles
    if(rand() % 5 < 2){ // Approximately every second
        FallingRect rect;
        rect.width = 10;
        rect.height = 20;
        rect.x = pidMenu.x + rand() % (int)(pidMenu.width - (int)rect.width);
        rect.y = pidMenu.y;
        rect.speed = 3.0f + static_cast<float>(rand() % 3);
        rect.alpha = 128.0f + static_cast<float>(rand() % 128); // Set random alpha between 128 and 255
        fallingRects.push_back(rect);
    }

    if(gameplayManager.timer.countdownFrames == (int)(3*(frames/4))){
        cmdInterpreter.outputLine("Flood: 25% complete.");
    }
    if(gameplayManager.timer.countdownFrames == (int)(frames/2)){
        cmdInterpreter.outputLine("Flood: 50% complete.");
    }
    if(gameplayManager.timer.countdownFrames == (int)((frames/4))){
        cmdInterpreter.outputLine("Flood: 75% complete.");
    }
    if(gameplayManager.timer.countdownFrames == 0){
        cmdInterpreter.outputLine("Flood: 100% complete.");
        cmdInterpreter.outputLine("Flood: Target firewall damaged.");
        gameplayManager.enemy.setHealth(gameplayManager.enemy.getHealth() - 30);
    }

    DrawTextC("PROCESS: FLOOD //", pidMenu.x + 10, pidMenu.y + 10, 20, primaryColor);
    // Fix the warning by correctly converting to char*
    std::string timeLeft = "EST. T.LEFT: " + std::to_string(gameplayManager.timer.countdownFrames / 60);
    DrawTextC(timeLeft.c_str(), pidMenu.x + 10, pidMenu.y + 30, 20, primaryColor);
}

void Pid::MailRender() {
    static int frameCounter = 0;
    static std::vector<Vector2> particles;
    static std::vector<Vector2> particleVelocities;

    // Animation duration in frames (10 seconds at 60 FPS)
    const int animationDuration = 10 * 60;

    // Envelope dimensions
    float envelopeWidth = 100.0f;
    float envelopeHeight = 60.0f;
    float envelopeX = pidMenu.x + (pidMenu.width - envelopeWidth) / 2;
    float envelopeY = pidMenu.y + (pidMenu.height - envelopeHeight) / 2;

    // Calculate the current frame of the animation
    frameCounter++;
    if (frameCounter > animationDuration) {
        frameCounter = 0; // Reset the frame counter
        particles.clear(); // Clear particles when animation resets
        particleVelocities.clear(); // Clear particle velocities
    }

    // Calculate the envelope flap angle based on the frame
    float progress = static_cast<float>(frameCounter) / animationDuration;
    float angle = (1.0f - progress) * -270.0f; // Close the flap from 90 degrees to 0 degrees

    // Draw the envelope body as a wireframe with thicker lines
    DrawRectangleLinesEx({envelopeX, envelopeY, envelopeWidth, envelopeHeight}, 3, primaryColor);

    // Draw the envelope flap as a wireframe with thicker lines
    Vector2 flapPoints[3] = {
        {envelopeX, envelopeY},
        {envelopeX + envelopeWidth, envelopeY},
        {envelopeX + envelopeWidth / 2, envelopeY - envelopeHeight / 2 * sin(DEG2RAD * angle)}
    };
    DrawLineEx(flapPoints[0], flapPoints[1], 3, primaryColor);
    DrawLineEx(flapPoints[1], flapPoints[2], 3, primaryColor);
    DrawLineEx(flapPoints[2], flapPoints[0], 3, primaryColor);

    // Generate particles
    if (frameCounter % 2 == 0) { // Generate a particle every 10 frames
        particles.push_back({envelopeX + envelopeWidth / 2, envelopeY + envelopeHeight / 2});
        float angle = static_cast<float>(rand() % 360) * DEG2RAD;
        float speed = 1.0f + static_cast<float>(rand() % 3);
        particleVelocities.push_back({cos(angle) * speed, sin(angle) * speed});
    }

    // Update and draw particles
    for (size_t i = 0; i < particles.size(); ) {
        particles[i].x += particleVelocities[i].x;
        particles[i].y += particleVelocities[i].y;
        DrawCircleV(particles[i], 2, primaryColor); // Draw particle as a small circle

        // Remove particle if it goes out of the pidMenu bounds
        if (particles[i].x < pidMenu.x || particles[i].x > pidMenu.x + pidMenu.width ||
            particles[i].y < pidMenu.y || particles[i].y > pidMenu.y + pidMenu.height) {
            particles.erase(particles.begin() + i);
            particleVelocities.erase(particleVelocities.begin() + i);
        } else {
            ++i;
        }
    }

    // Draw additional text
    DrawTextC("PROCESS: SMTP//", pidMenu.x + 10, pidMenu.y + 10, 20, primaryColor);
    // Fix the warning by correctly converting to char*
    std::string timeLeft = "EST. T.LEFT: " + std::to_string(gameplayManager.timer.countdownFrames / 60);
    DrawTextC(timeLeft.c_str(), pidMenu.x + 10, pidMenu.y + 30, 20, primaryColor);
}