#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char songName[100];
    char artist[100];
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(char songName[], char artist[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->songName, songName);
    strcpy(newNode->artist, artist);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, char songName[], char artist[]) {
    struct Node* newNode = createNode(songName, artist);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void deleteNode(struct Node** head, char songName[]) {
    struct Node* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->songName, songName) == 0) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            if (temp == *head) {
                *head = temp->next;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
    printf("Song '%s' not found in the playlist.\n", songName);
}

void moveSong(struct Node** head, char songName[]) {
    struct Node* temp = *head;
    struct Node* target = NULL;
    while (temp != NULL) {
        if (strcmp(temp->songName, songName) == 0) {
            target = temp;
            break;
        }
        temp = temp->next;
    }
    if (target == NULL) {
        printf("Song '%s' not found in the playlist.\n", songName);
        return;
    }
    if (target->prev != NULL) {
        target->prev->next = target->next;
    }
    if (target->next != NULL) {
        target->next->prev = target->prev;
    }
    target->prev = NULL;
    target->next = *head;
    if (*head != NULL) {
        (*head)->prev = target;
    }
    *head = target;
    printf("Song '%s' moved to the beginning of the playlist.\n", songName);
}

void sortPlaylist(struct Node** head) {
    struct Node *current, *index;
    char tempSong[100], tempArtist[100];

    if (*head == NULL) {
        printf("Playlist is empty.\n");
        return;
    } else {
        for (current = *head; current->next != NULL; current = current->next) {
            for (index = current->next; index != NULL; index = index->next) {
                if (strcmp(current->songName, index->songName) > 0) {
                    strcpy(tempSong, current->songName);
                    strcpy(tempArtist, current->artist);
                    strcpy(current->songName, index->songName);
                    strcpy(current->artist, index->artist);
                    strcpy(index->songName, tempSong);
                    strcpy(index->artist, tempArtist);
                }
            }
        }
        printf("Playlist sorted in alphabetical order.\n");
    }
}

void displayPlaylist(struct Node* head) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
    } else {
        printf("Playlist:\n");
        struct Node* temp = head;
        while (temp != NULL) {
            printf("Song: %s, Artist: %s\n", temp->songName, temp->artist);
            temp = temp->next;
        }
    }
}

int main() {
    struct Node* playlist = NULL;
    char songName[100], artist[100];
    int choice;

    while (1) {
        printf("\nPlaylist Management System\n");
        printf("1. Add Song\n");
        printf("2. Delete Song\n");
        printf("3. Reorder Song\n");
        printf("4. Sort Playlist\n");
        printf("5. Display Playlist\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter song name: ");
                scanf("%s", songName);
                printf("Enter artist name: ");
                scanf("%s", artist);
                insertNode(&playlist, songName, artist);
                printf("Song added to the playlist.\n");
                break;
            case 2:
                printf("Enter song name to delete: ");
                scanf("%s", songName);
                deleteNode(&playlist, songName);
                break;
            case 3:
                printf("Enter song name to move to the beginning: ");
                scanf("%s", songName);
                moveSong(&playlist, songName);
                break;
            case 4:
                sortPlaylist(&playlist);
                break;
            case 5:
                displayPlaylist(playlist);
                break;
            case 6:
                // Free memory - cleanup before exiting
                while (playlist != NULL) {
                    struct Node* temp = playlist;
                    playlist = playlist->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
