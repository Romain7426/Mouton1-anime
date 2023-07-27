#include <unistd.h> /* https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html */ /* https://en.wikipedia.org/wiki/Unistd.h */ 
#include <stdlib.h> // man 3 arc4random 
#include <time.h> // man 3 clock 

#include "lib.ci"
#include "lib__llfixed.ci"

static const char * argv0; 




int main(const int argc, const char * argv[]) { 
  if (1 > argc) { 
    write_string(STDERR_FILENO, "Does not make sense - ARGC is lower than 1: "); 
    write_long_long_int(STDERR_FILENO, argc); 
    write_eol(STDERR_FILENO); 
    return 4; 
  }; 
  argv0 = argv[0]; 
  goto label__body; 
  
  
  label__error__exit: { 
    return 1; 
  }; 
  
  label__exit: { 
    return 0; 
  }; 
  
  label__body: { 
    long long int start_value; 
    arc4random_buf(&start_value, sizeof(start_value)); 
    //start_value = 10000; 
    //start_value = 1073741829; 
    //enum { low_mask2 = (((1 << 30) - 1) << 1) + 1 }; 
    //enum { low_mask2 = (((1 << 30) - 1) << 2) + 3 }; 
    //start_value &= (unsigned long long int)low_mask2; 
    start_value = (((unsigned long long int)start_value) >> 1); 
    //start_value = (((unsigned long long int)start_value) >> 31); 
    //start_value = 490435303397; 52766323769; 7204348885; 5711259197; 
    //start_value = 5924557118; 
    //start_value = 6420108144320270416;
    //start_value = 6420108144320270; 
    
#if 1
    enum { print_huh = false }; 
    //enum { TRIALS = 2000000000 }; 
    //enum { TRIALS = 1000000000 }; 
    enum { TRIALS = 100000000 }; 
#else 
    enum { print_huh = true }; 
    enum { TRIALS = 4 }; 
#endif 
    const clock_t u1 = clock(); 
    { 
      long long int t = start_value; 
      if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t); 
      for (int i = 0; i < TRIALS; i++) { 
#if 0 
	arc4random_buf(&start_value, sizeof(start_value)); 
	start_value = (((unsigned long long int)start_value) >> 1); 
#endif 
	//t /= 2; 
	t /= 10; 
	if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t); 
      }; 
    }; 
    const clock_t u2 = clock(); 
    const long long int u0 = (u2 - u1) / CLOCKS_PER_SEC; 

    if (print_huh) write_string_ln(STDOUT_FILENO, " --- "); 
    
    const clock_t v1 = clock(); 
    { 
      long long int t = start_value; 
      if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t); 
      for (int i = 0; i < TRIALS; i++) { 
#if 0 
	arc4random_buf(&start_value, sizeof(start_value)); 
	start_value = (((unsigned long long int)start_value) >> 1); 
#endif 
	//t >>= 1; 
#if 0 
	t >>= 1; 
	t = (t >> 3) + (t >> 4) + (t >> 7) + (t >> 8) + (t >> 11) + (t >> 12) + (t >> 15) + (t >> 16) + (t >> 19) + (t >> 20) + (t >> 23) + (t >> 24) + (t >> 27) + (t >> 28) + (t >> 31) + (t >> 32); 
#elif 0
	t >>= 1; 
	t = (t >>  3) + (t >>  4) + (t >>  7) + (t >>  8) + (t >> 11) + (t >> 12) + (t >> 15) + (t >> 16) + (t >> 19) + (t >> 20) + (t >> 23) + (t >> 24) + (t >> 27) + (t >> 28) + (t >> 31) + (t >> 32) 
//	  + (t >> 35) + (t >> 36) + (t >> 39) + (t >> 40) + (t >> 43) + (t >> 44) + (t >> 47) + (t >> 48) + (t >> 51) + (t >> 52) + (t >> 55) + (t >> 56) + (t >> 59) + (t >> 60) + (t >> 63) + (t >> 64); 
	  + (t >> 35) + (t >> 36) + (t >> 39) + (t >> 40) + (t >> 43) + (t >> 44) + (t >> 47) + (t >> 48) + (t >> 51) + (t >> 52) + (t >> 55) + (t >> 56) + (t >> 59) + (t >> 60) + (t >> 63);
#elif 0
	const long long int t2 = t + (t << 1); 
	t = (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) + (t2 >> 32) 
	  + (t2 >> 36) + (t2 >> 40) + (t2 >> 44) + (t2 >> 48) + (t2 >> 52) + (t2 >> 56) + (t2 >> 60); // + (t2 >> 64); 
	t >>= 1; 
#elif 0
	const long long int t2 = t + (t >> 1); 
	t = (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) + (t2 >> 32) 
	  + (t2 >> 36) + (t2 >> 40) + (t2 >> 44) + (t2 >> 48) + (t2 >> 52) + (t2 >> 56) + (t2 >> 60); // + (t2 >> 64); 
#elif 0
	const long long int t2 = t + (t << 1); 
	t = (t2 >>  5) + (t2 >>  9) + (t2 >> 13) + (t2 >> 17) + (t2 >> 21) + (t2 >> 25) + (t2 >> 29) + (t2 >> 33) 
	  + (t2 >> 37) + (t2 >> 41) + (t2 >> 45) + (t2 >> 49) + (t2 >> 53) + (t2 >> 57) + (t2 >> 61); // + (t2 >> 65); 
#elif 0
	enum { t2 = (1 << 30) + (1 << 29) }; 
	enum { t3 
	  = (t2 >>  5) + (t2 >>  9) + (t2 >> 13) + (t2 >> 17) + (t2 >> 21) + (t2 >> 25) + (t2 >> 29) + (t2 >> 33) 
	  + (t2 >> 37) + (t2 >> 41) + (t2 >> 45) + (t2 >> 49) + (t2 >> 53) + (t2 >> 57) + (t2 >> 61) // + (t2 >> 65) 
	}; 
	//enum { t4 = (t2 >>  5) + (t2 >>  9) + (t2 >> 13) + (t2 >> 17) + (t2 >> 21) + (t2 >> 25) + (t2 >> 29) + (t2 >> 33) }; 
	//enum { t4 = (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) + (t2 >> 32) }; 
	//enum { t4 = (t2 >>  2) + (t2 >>  6) + (t2 >> 10) + (t2 >> 14) + (t2 >> 18) + (t2 >> 22) + (t2 >> 26) + (t2 >> 30) }; 
	enum { t4 = 1 + (t2 >>  2) + (t2 >>  6) + (t2 >> 10) + (t2 >> 14) + (t2 >> 18) + (t2 >> 22) + (t2 >> 26) + (t2 >> 30) }; 
	t *= t4; 
	t >>= 32; 
	//t++; 
#elif 0
	enum { t2 = (1 << 30) + (1 << 29) }; 
	enum { t3 
	  = (t2 >>  5) + (t2 >>  9) + (t2 >> 13) + (t2 >> 17) + (t2 >> 21) + (t2 >> 25) + (t2 >> 29) + (t2 >> 33) 
	  + (t2 >> 37) + (t2 >> 41) + (t2 >> 45) + (t2 >> 49) + (t2 >> 53) + (t2 >> 57) + (t2 >> 61) // + (t2 >> 65) 
	}; 
	//enum { t4 = (t2 >>  5) + (t2 >>  9) + (t2 >> 13) + (t2 >> 17) + (t2 >> 21) + (t2 >> 25) + (t2 >> 29) + (t2 >> 33) }; 
	//enum { t4 = (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) + (t2 >> 32) }; 
	//enum { t4 = (t2 >>  2) + (t2 >>  6) + (t2 >> 10) + (t2 >> 14) + (t2 >> 18) + (t2 >> 22) + (t2 >> 26) + (t2 >> 30) }; 
	enum { t4 = 1 + (t2 >>  2) + (t2 >>  6) + (t2 >> 10) + (t2 >> 14) + (t2 >> 18) + (t2 >> 22) + (t2 >> 26) + (t2 >> 30) }; 
	//enum { low_mask = (1 << 32) - 1 }; 
	//enum { low_mask = (((1 << 31) - 1) << 1) + 1 }; 
	enum { low_mask = (((1 << 30) - 1) << 2) + 3 }; 
	long long int t_high = (t >> 32); 
	long long int t_low  = t & (unsigned) low_mask; 
	t_low *= t4; 
	//t_low >>= 32; 
	t_high *= t4; 
	//t_high >>= 32; 
	t = t_high + (t_low >> 32); 
	//t++; 
#elif 0
	// That one works. Gain by 30%: 100 VS 150. 
	// There might be some rounding errors - I haven’t found any of them yet. 
	// -- 
	// The gain is significant (30% faster). However. I would need a proof that the result is always accurate (that the rounding is always correct). 
	// -- 
	// For the record, without the rounding steps, the algorithm is 50% faster. 
	// -- 
	// Rounding error with:    
	//start_value = 6420108144320270416;
	enum { t2 = (1 << 30) + (1 << 29) }; 
	//enum { t4 = 1 + (t2 >>  2) + (t2 >>  6) + (t2 >> 10) + (t2 >> 14) + (t2 >> 18) + (t2 >> 22) + (t2 >> 26) + (t2 >> 30) }; 
	enum { t4 = (t2 >>  0) + (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) }; 
	//enum { low_mask = (1 << 32) - 1 }; 
	//enum { low_mask = (((1 << 31) - 1) << 1) + 1 }; 
	enum { low_mask = (((1 << 30) - 1) << 2) + 3 }; 
	long long int t_high = (t >> 32); 
	long long int t_low  = t & (unsigned) low_mask; 
	t_low *= t4; 
	//t_low >>= 32; 
	t_high *= t4; 
	//t_high >>= 32; 
	//t = t_high + (t_low >> 32); 
	//t >>= 2; 
	//t  = (t_high >> 2) + (t_low >> 34); 
	//t += (t_high >> 34); 
	//t  = (t_high >> 2) + (t_low >> 34) + (t_high >> 34);  
	t  = (t_high ) + (t_low >> 32) + (t_high >> 32);  
	//const int round_huh = ((t & 3) >= 2); 
	const int round_huh = ((t & 3) >= 3); 
	t >>= 2;
	if (round_huh) t++; 
	//t++; 
#elif 1
	// That one works. Gain by 24%: 1450 VS 1068 
	// For the record, without the rounding steps, the algorithm is 31% faster (1441 vs 987). 
	// -- 
	// According to several tests of 100000000, there is no rounding error. 
	enum { t2 = (1  << 30) + (1  << 29) }; 
	enum { t4 = (t2 >>  0) + (t2 >>  4) + (t2 >>  8) + (t2 >> 12) + (t2 >> 16) + (t2 >> 20) + (t2 >> 24) + (t2 >> 28) }; 
	enum { low_mask = (((1 << 30) - 1) << 2) + 3 }; 
	const long long int t_given = t; 
	long long int t_high = (t >> 32); 
	long long int t_low  = t & ((unsigned) low_mask); 
	t_low  *= t4; 
	t_high *= t4; 
	t  = (t_high ) + (t_low >> 32) + (t_high >> 32);  
	// Due to the loss of information, this new 't' is always lower than the incoming 't'. 
	// How great is the loss of information? 
	// This loss of information can be assumed to be less than 10. (According to tests, it’s less than 5.) 
	// However, between '19' and '10', no rounding should be done, 
	// while between '20' and '19', rounding should be done. 
	// The figure [last 't' x 10] is a multiple of ten. So, there is a rounding error if the difference between that number and the given number is greater or equal than ten. 
	t >>= 2;
	const int round_huh = ((t_given - ((t << 3) + (t  << 1))) >= 10); 
	if (round_huh) t++; 
#if 0 
	if (t != (t_given / 10)) { 
	  assert(false); 
	};
#endif
#elif 1
	assert(false); 
	// I have to implement another one: 
	//  - Finding by the greatest power of 10 lower than the number. 
#endif 
#if 0 
	if (print_huh) write_long_long_int_ln(STDOUT_FILENO, low_mask); 
	if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t2); 
	if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t3); 
#endif 
	if (print_huh) write_long_long_int_ln(STDOUT_FILENO, t); 

      }; 
    }; 
    const clock_t v2 = clock(); 
    const long long int v0 = (v2 - v1) / CLOCKS_PER_SEC; 
    
    
    write_string(STDOUT_FILENO, "Standard function time: "); 
    //write_long_long_int(STDOUT_FILENO, u0); 
    //write_eol(STDOUT_FILENO); 
    write_long_long_int(STDOUT_FILENO, u2 - u1); 
    write_eol(STDOUT_FILENO); 

    write_string(STDOUT_FILENO, "Sophisticated function time: "); 
    //write_long_long_int(STDOUT_FILENO, v0); 
    //write_eol(STDOUT_FILENO); 
    write_long_long_int(STDOUT_FILENO, v2 - v1); 
    write_eol(STDOUT_FILENO); 
    goto label__exit; 
  }; 
  
  
}; 


