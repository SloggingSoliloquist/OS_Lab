#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <thread>

struct Message {
    int length;
    char s[256];
};

void write_message(int write_end) {
    std::string buf;

    while (true) {
        std::cout << "Enter your message: ";
        std::getline(std::cin, buf);

        Message message{};
        message.length = std::min((int)buf.size(), 255);

        memcpy(message.s, buf.data(), message.length);
        message.s[message.length] = '\0';

        write(write_end, &message, sizeof(message));

        if (buf == "bye")
            break;
    }
}

void read_message(int read_end) {
    while (true) {
        Message message{};

        ssize_t n = read(read_end, &message, sizeof(message));

        if (n == 0) {
            std::cout << "Other side closed the connection\n";
            break;
        }

        if (n < 0) {
            perror("read");
            break;
        }

        std::cout << "Received: ";
        std::cout.write(message.s, message.length);
        std::cout << std::endl;

        if (std::string(message.s, message.length) == "bye")
            break;
    }
}

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    int write_end = open(fifo1, O_WRONLY);
    int read_end = open(fifo2, O_RDONLY);

    std::thread reader(read_message, read_end);
    std::thread writer(write_message, write_end);

    writer.join();
    reader.join();

    close(read_end);
    close(write_end);

    return 0;
}