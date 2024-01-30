#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    int points = 0;
    char user_answer;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char points_str;

    char buffer[256];
    char msg[256] = "Client Hello";
    char next[256] = "x";
    char jebaccpp[256] = "5";
    char delim[] = "::";
    std::ostringstream ss;
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    n = read(sockfd, buffer, 255);
    //printf("%s\n", buffer);
    //
    std::cout << "Hello User ";
    read(sockfd, buffer, 255);
    std::cout << buffer << std::endl;
    memset(buffer, 0, sizeof buffer);
    write(sockfd, msg, sizeof msg);


    while (sockfd)
    {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        //std::cout << points << std::endl;
        //std::cout << bool(buffer[0] == 'E') << std::endl;



        if (buffer[0] == 'E') {
            points_str = (char)points;

            std::string s = std::to_string(points);
            char const *pchar = s.c_str();  //use char const* as target type

            //std::cout << "W pretli koncowej" << std::endl;
            ss << points;
            //std::cout << points << std::endl;
            //std::cout << pchar << std::endl;
            write(sockfd, pchar, sizeof next);
            //write(sockfd, points_str.c_str(), points_str.size());
            read(sockfd, buffer, 255);
            //std::cout << "Twoje punkty to: " << buffer[0] << std::endl;
            read(sockfd, buffer, 255);
            std::cout << buffer << std::endl;

            close(sockfd);
            return 0;

        }

        if (n < 0)
            error("ERROR reading from socket");

        char *token = strtok(buffer, "::");
        printf("%s\n", token);
        token = strtok(NULL, delim);
        printf("A. %s\n", token);
        token = strtok(NULL, delim);
        printf("B. %s\n", token);
        token = strtok(NULL, delim);
        printf("C. %s\n", token);

        std::cout << "Your answer (A/B/C): " << std::endl;
        std::cin >> user_answer;

        token = strtok(NULL, delim);

        if(user_answer == *token) {

            points +=1;

        }
        write(sockfd, next, sizeof next);
        //std::cout << points <<std::endl;

    }

    close(sockfd);
    return 0;
}
