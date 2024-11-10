#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

void playMusic(const char* songPath) {
    char command[MAX_PATH_LENGTH + 50]; // Adjust length based on the command
    snprintf(command, sizeof(command), "vlc --play-and-exit \"%s\" &", songPath);
    int result = system(command);
    if (result == -1) {
        perror("Error playing music");
    }
}

void pauseMusic() {
    int result = system("pkill -STOP vlc");
    if (result == -1) {
        perror("Error pausing music");
    }
}

void resumeMusic() {
    int result = system("pkill -CONT vlc");
    if (result == -1) {
        perror("Error resuming music");
    }
}

void stopMusic() {
    int result = system("pkill vlc");
    if (result == -1) {
        perror("Error stopping music");
    }
}

int main() {
    int choice;
    char songPath[MAX_PATH_LENGTH] = "downloaded_song.mp3"; // Default song

    while (1) {
        printf("\n\n--- Music Player Menu ---\n");
        printf("1. Play Music\n");
        printf("2. Pause Music\n");
        printf("3. Resume Music\n");
        printf("4. Stop Music\n");
        printf("5. Add New Song\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear the buffer
            continue;
        }
        getchar(); // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                playMusic(songPath);
                break;
            case 2:
                pauseMusic();
                break;
            case 3:
                resumeMusic();
                break;
            case 4:
                stopMusic();
                break;
            case 5:
                printf("Enter the path of the new song: ");
                fgets(songPath, MAX_PATH_LENGTH, stdin);
                songPath[strcspn(songPath, "\n")] = '\0'; // Remove newline character
                printf("New song added: %s\n", songPath);
                break;
            case 6:
                stopMusic();  // Make sure to stop any playing music before exiting
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}
