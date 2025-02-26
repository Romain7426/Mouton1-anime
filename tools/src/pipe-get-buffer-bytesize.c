#include "lib.ci"

#include <fcntl.h>  /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html  */ 

int main(const int argc, const char * argv[]) { 
  int my_pipe[2];
  char buffer[INT16_MAX << 1];
  if (-1 == pipe(my_pipe)) return -1;
  //fcntl(my_pipe[0], F_SETFL, O_NONBLOCK); // RL: N’empêche pas le blocage. 
  fcntl(my_pipe[1], F_SETFL, O_NONBLOCK); // RL: Empêche le blocage. 
  const ssize_t written_nb = write(my_pipe[1],buffer,sizeof(buffer)); 
  if (-1 == written_nb) return -2;
  if (0 > written_nb) return -3;
  write_llint_ln(STDOUT_FILENO, written_nb); 
  close(my_pipe[0]);
  close(my_pipe[1]);
  return 0; 
};
