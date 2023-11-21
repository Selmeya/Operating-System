#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100

// Define a structure for the message
struct Message {
    long mtype; // Message type (must be greater than 0)
    char mtext[MAX_MESSAGE_SIZE]; // Message content
};

int main() {
    key_t key = ftok("message_queue_example", 1); // Generate a unique key

    // Create a message queue
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Process 1 (Sender)
    struct Message message1;
    message1.mtype = 1; // Message type must be greater than 0
    printf("Enter message to send: ");
    fgets(message1.mtext, MAX_MESSAGE_SIZE, stdin);

    // Send message to the queue
    if (msgsnd(msgid, &message1, sizeof(message1.mtext), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    // Process 2 (Receiver)
    struct Message message2;

    // Receive message from the queue
    if (msgrcv(msgid, &message2, sizeof(message2.mtext), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s", message2.mtext);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

