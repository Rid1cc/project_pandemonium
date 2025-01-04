#include "Pid.h"
#include "../headers/globals.h"
#include "gameplay_vars.h"

// Constructor to initialize PID menu properties
Pid::Pid() {
    pidMenu = {screen.x + 900, screen.y + 97, 249, 540};
    idle = true;
    displayEnemyIpFrames = 0;
}

// Render the PID menu
void Pid::RenderIdle() {
    DrawRectangleRec(pidMenu, BLACK);
    DrawTextC("NO", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) - 50, 40, primaryColor);
    DrawTextC("PROCESS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
    DrawTextC("ACTIVE", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) + 50, 40, primaryColor);
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
                DrawTextC("SILENT DRAIN", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                if(gameplayManager.timer.countdownFrames == 1){
                    cmdInterpreter.outputLine("Netscan: Silent Drain complete.");
                    cmdInterpreter.outputLine("Netscan: Remaining IP's: " + std::to_string(gameplayManager.selectedIpPool.size()));
                }
                break;
            case MAIL:
                DrawTextC("MAIL", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case DDOS:
                DrawTextC("DDOS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case ADD_BOTNET:
                DrawTextC("ADD BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case ATK_BOTNET:
                DrawTextC("ATTACK BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
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
