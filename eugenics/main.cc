// Group 15: CSCE315-503 Project 3
// Eugenics
// main.cc

#include <iostream>
#include <string>

#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <cstdlib>  //exit

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "getopts.h"
#include "utility.h"

void error(const char *msg) {
  perror(msg);
  std::exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  // get algorithm from CLI
  EugenicsConfig config = getOpts(argc, argv);
  if (config.algol == GENETIC) {
    errlog("Running Genetic Algorithm");
  } else if (config.algol == TRADITIONAL) {
    errlog("Running Traditional Algorithm");
  }

  // create socket
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];

  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    std::exit(EXIT_SUCCESS);
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    std::exit(EXIT_SUCCESS);
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");
  printf("Please enter the message: ");
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0) error("ERROR writing to socket");
  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);
  if (n < 0) error("ERROR reading from socket");
  printf("%s\n", buffer);
  close(sockfd);

  std::exit(EXIT_SUCCESS);
}
