#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TMP 100
#define MAX_LINKED 100

struct movie{
  int serial_number; // 영화 시리얼 넘버
  char *title; // 영화 이름 포인터
  char *genre; // 장르 이름 포인터
  struct director_in_movie *director_m; // 감독명 및, 해당 디렉터 노드 정보 저장
  int year;
  int movie_time;
  struct actor_in_movie *actor_m ; // 배우명 및,  다음 배우 구조체 노드, 해당 배우 구조체 노드
  struct movie *next; // 다음 movie의 구조체
} ;

struct director_in_movie { // 감독명 및, 해당 디렉터 노드 정보 저장
  char *name;
  struct director *directr_node;
} ;

struct actor_in_movie { // 배우명 및,  다음 배우 구조체 노드, 해당 배우 구조체 노드
  char *name;
  struct actor_in_movie *next;
  struct director *actor_node;
} ;

struct director {
  int serial_number;
  char *name; // 감독 이름 포인터
  char sex; //성별
  char *birth; // 생년월일 포인터
  struct movie_in_director *movie_d; // 대표작 포인터로 대표작명, 다음 대표작 자기참조 포인터, 해당 대표작 구조체 노드
  struct director *next; // 다음 감독 노드
} ;

struct movie_in_director { // 대표작 포인터로 대표작명, 다음 대표작 자기참조 포인터, 해당 대표작 구조체 노드
  char *name;  // 영화 이름
  struct movie_in_director *next; // 다음 영화 노드
  struct movie *movie_node; // 해당 영화 구조체 노드
} ;

struct actor {
  int serial_number; //시리얼 넘버
  char *name; // 이름 포인터
  char sex; // 성별 정보
  char *birth; // 생일 포인터
  struct movie_in_actor *movie_a; // 출연작 영화 구조체 퐁니터
  struct actor *next; // 다음 배우 구조체 노드
} ;

  struct movie_in_actor {
    char *name; // 영화 이름 포인터
    struct movie_in_actor *next; //다음 영화 노드
    struct movie *movie_node;  // 해당 영화 구조체 노드
};

struct main_struct_ptr {
  struct movie *movie_ptr;
  struct actor *actor_ptr;
  struct director *director_ptr;
};



void get_data(struct main_struct_ptr *data_ptr);
void scan_word(FILE *optr, char *tmp_data);
int str_devider (char *str);
void get_movie(struct main_struct_ptr *data_ptr);
void add_movie (FILE *optr, struct movie *movie_ptr);
void scan_serial_number_m(FILE *optr, struct movie *movie_ptr);
void scan_title_m(FILE *optr, struct movie *movie_ptr);
void scan_genre_m(FILE *optr, struct movie *movie_ptr);
void scan_director_m(FILE *optr, struct movie *movie_ptr);
void scan_year_m(FILE *optr, struct movie *movie_ptr);
void scan_movie_time_m(FILE *optr, struct movie *movie_ptr);
void scan_actor_m(FILE *optr, struct movie *movie_ptr);
void get_director(struct main_struct_ptr *data_ptr);
void add_director (FILE *optr, struct director *director_ptr);
void scan_serial_number_d(FILE *optr, struct director *director_ptr);
void scan_name_d(FILE *optr, struct director *director_ptr);
void scan_sex_d(FILE *optr, struct director *director_ptr);
void scan_birth_d(FILE *optr, struct director *director_ptr);
void scan_title_d(FILE *optr, struct director *director_ptr);
void get_actor(struct main_struct_ptr *data_ptr);
void add_actor (FILE *optr, struct actor *actor_ptr);
void scan_serial_number_a(FILE *optr, struct actor *actor_ptr);
void scan_title_a(FILE *optr, struct actor *actor_ptr);
void scan_sex_a(FILE *optr, struct actor *actor_ptr);
void scan_birth_a(FILE *optr, struct actor *actor_ptr);
void scan_title_a(FILE *optr, struct actor *actor_ptr);
void clean_word(char *tmp_data);


void get_data(struct main_struct_ptr *data_ptr){
  get_movie(data_ptr);
  printf(" \n \n \n");
 get_director(data_ptr);
 printf(" \n \n \n");
 get_actor(data_ptr);
}

void scan_word(FILE *optr, char *tmp_data){
  for (int i = 0 ; i < 100 ; i++ ) {
    fscanf(optr, "%c", (tmp_data + i));
    if ( *(tmp_data + i) == ':')
      break;
    if ( *(tmp_data + i) == '\n')
      break;
    if ( *(tmp_data+i) == EOF)
      break;
  }
  *(tmp_data + (strlen(tmp_data)-1)) = 0;
}


int str_devider (char *str) {
  int count = 0;
  for (int i=0; count<4*MAX_TMP; i++){
    if (*(str+i) == ',')
      break;
    if(*(str+i) == '\n')
      break;
    count ++;
  }
  return count;
}

void clean_word(char *tmp_data){
  for (int i=0; i<MAX_TMP ; i++){
    if ( *(tmp_data + i) != 0)
      *(tmp_data + i) = 0;
    else
      break;
  }
}


void get_movie(struct main_struct_ptr *data_ptr){
  FILE *optr;
  optr = fopen ("test1.txt", "r");
  (data_ptr -> movie_ptr) = malloc(sizeof(struct movie));
  struct movie *tmp_movie_ptr;
  tmp_movie_ptr = (data_ptr->movie_ptr);

    while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
      {
        char *mode;
        mode = malloc(1*MAX_TMP); //모드 최고 글자수가 6개 + 1이므로
        scan_word(optr, mode);
        if (strcmp("add", mode) == 0) {
          printf("1: %s\n", mode);
          add_movie(optr, (tmp_movie_ptr));
          (tmp_movie_ptr -> next) = malloc (sizeof(struct movie));
          tmp_movie_ptr = (tmp_movie_ptr -> next);
          continue;
      }

      if (*mode == 0)
        break;


      free(mode);

          }
    fclose(optr);
}


void add_movie (FILE *optr, struct movie *movie_ptr) {
  scan_serial_number_m(optr, movie_ptr);
  scan_title_m(optr, movie_ptr);
  scan_genre_m(optr, movie_ptr);
  scan_director_m(optr,movie_ptr);
  scan_year_m(optr,movie_ptr);
  scan_movie_time_m(optr, movie_ptr);
  scan_actor_m(optr, movie_ptr);
  printf("********************\n  ");
}


void scan_serial_number_m(FILE *optr, struct movie *movie_ptr) {
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
  (movie_ptr -> serial_number) = atoi(tmp_name);
  printf("2:%d\n",(movie_ptr -> serial_number));
}

void scan_title_m(FILE *optr, struct  movie *movie_ptr){
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
  (movie_ptr->title) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
  strcpy((movie_ptr->title),tmp_name);
  printf("3:%s\n", movie_ptr->title);
}

void scan_genre_m(FILE *optr,struct movie * movie_ptr){
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name);
  (movie_ptr->genre) = malloc ((strlen(tmp_name)+1));
  strcpy((movie_ptr->genre),tmp_name);
  printf("4:%s\n", movie_ptr->genre);
}

void scan_director_m(FILE *optr, struct movie *movie_ptr){
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name);
  (movie_ptr->director_m) = malloc (sizeof(struct director_in_movie)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
  ((movie_ptr->director_m)->name) = malloc ((strlen(tmp_name)+1));
  strcpy(((movie_ptr->director_m)->name), tmp_name);
  printf("5:%s\n", movie_ptr->director_m->name);
}

void scan_year_m(FILE *optr, struct movie *movie_ptr){
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name);
  (movie_ptr -> year) = atoi(tmp_name);
  printf("6:%d\n",movie_ptr -> year);
}

void scan_movie_time_m(FILE *optr, struct movie *movie_ptr){
  char *tmp_name;
  tmp_name = malloc(1*MAX_TMP);
  scan_word(optr, tmp_name);
  (movie_ptr -> movie_time) = atoi(tmp_name);
  printf("7:%d\n",movie_ptr-> movie_time);
}

void scan_actor_m(FILE *optr, struct movie *movie_ptr){

  (movie_ptr->actor_m) = malloc (sizeof(struct actor_in_movie)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
   movie_ptr->actor_m->next = 0;
  struct actor_in_movie *tmp_actor_ptr;
  tmp_actor_ptr = movie_ptr->actor_m;

  char *tmp_str;
  int flag = 1;
  tmp_str = malloc(4*MAX_TMP);
  scan_word(optr, tmp_str);
  printf("point : %s\n", tmp_str);

  while ((flag = str_devider(tmp_str)) != 0) {

    if (*tmp_str == 0)
      break;

    char *tmp_actor;
    tmp_actor = malloc (flag + 1);
    for (int i = 0; i< flag ; i++){
      *(tmp_actor + i) = *(tmp_str + i);
    }
    tmp_str = tmp_str + flag + 1;

    (tmp_actor_ptr->name) = malloc (flag + 1);
    strcpy((tmp_actor_ptr->name), tmp_actor);
    (tmp_actor_ptr->next) = malloc (sizeof(struct actor_in_movie));
    printf("8:%s\n", tmp_actor_ptr->name);
    tmp_actor_ptr = tmp_actor_ptr -> next;

  }
}

// for (int i = 0; i < MAX_LINKED; i++){
//   if ( (tmp_actor_ptr->next) == 0)
//     break;
//   else
//     *tmp_actor_ptr = *tmp_actor_ptr -> next;
// }


void get_director(struct  main_struct_ptr *data_ptr){
  FILE *optr;
  optr = fopen ("test2.txt", "r");
  (data_ptr -> director_ptr) = malloc(sizeof(struct director));
  struct director *tmp_director_ptr;
  tmp_director_ptr = (data_ptr->director_ptr);

  while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
    {
      char *mode;
      mode = malloc(1*MAX_TMP); //모드 최고 글자수가 6개 + 1이므로
      printf("point is here :  %s\n", mode);
      scan_word(optr, mode);
      printf("%s\n", mode);
      if (strcmp("add", mode) == 0) {
        printf("1: %s\n", mode);
        add_director(optr, (tmp_director_ptr));
        (tmp_director_ptr -> next) = malloc (sizeof(struct director));
        tmp_director_ptr = (tmp_director_ptr -> next);
      }

      if ( *mode == 0)
          break;

      else
          continue;


      // else
      //   printf("잘못된 데이터 형식입니다\n");
    }

    fclose(optr);
  }



  void add_director (FILE *optr, struct director *director_ptr) {
    scan_serial_number_d(optr, director_ptr);
    scan_name_d(optr, director_ptr); // title
    scan_sex_d(optr, director_ptr); // new one
    scan_birth_d(optr, director_ptr); // genre
    scan_title_d(optr, director_ptr); //acotr
    printf("********************\n  ");
  }

  void scan_serial_number_d(FILE *optr, struct director *director_ptr) {
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
    (director_ptr -> serial_number) = atoi(tmp_name);
    printf("2:%d\n",(director_ptr -> serial_number));
  }

  void scan_name_d(FILE *optr, struct director *director_ptr){
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
    (director_ptr->name) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
    strcpy((director_ptr->name),tmp_name);
    printf("3:%s\n", director_ptr->name);
  }

  void scan_sex_d (FILE *optr, struct director *director_ptr){
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
    (director_ptr -> sex) = *tmp_name;
    printf("2:%c\n",(director_ptr -> sex));
  }



  void scan_birth_d(FILE *optr, struct director *director_ptr){
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name);
    (director_ptr->birth) = malloc ((strlen(tmp_name)+1));
    strcpy((director_ptr->birth),tmp_name);
    printf("4:%s\n", director_ptr->birth);
  }

  void scan_title_d(FILE *optr, struct director *director_ptr){

    (director_ptr->movie_d) = malloc (sizeof(struct movie_in_director)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
    director_ptr->movie_d->next = 0;
    struct movie_in_director *tmp_movie_ptr;
    tmp_movie_ptr = director_ptr->movie_d;

    char *tmp_str;
    int flag = 1;
    tmp_str = malloc(4*MAX_TMP);
    scan_word(optr, tmp_str);
    printf("point : %s\n", tmp_str);
    printf("\n tmp_str is here : %s \n", tmp_str);

    while ((flag = str_devider(tmp_str)) != 0) {

      if (*tmp_str == 0)
      break;

      char *tmp_title;
      tmp_title = malloc (flag + 1);

      for (int i = 0; i< flag ; i++){
        *(tmp_title + i) = *(tmp_str + i);
      }
      tmp_str = tmp_str + flag + 1;

      (tmp_movie_ptr->name) = malloc (flag + 1);
      strcpy((tmp_movie_ptr->name), tmp_title);
      (tmp_movie_ptr->next) = malloc (sizeof(struct movie_in_director));
      printf("8:%s\n", tmp_movie_ptr->name);
      tmp_movie_ptr = tmp_movie_ptr -> next;
    }
  }


  void get_actor(struct  main_struct_ptr *data_ptr){
    FILE *optr;
    optr = fopen ("test3.txt", "r");
    (data_ptr -> actor_ptr) = malloc(sizeof(struct actor));
    struct actor *tmp_actor_ptr;
    tmp_actor_ptr = (data_ptr->actor_ptr);
    while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
      {
        char *mode;
        mode = malloc(1*MAX_TMP); //모드 최고 글자수가 6개 + 1이므로
        scan_word(optr, mode);
        printf("%s\n", mode);
        if (strcmp("add", mode) == 0) {
          printf("1: %s\n", mode);
          add_actor(optr, (tmp_actor_ptr));
          (tmp_actor_ptr -> next) = malloc (sizeof(struct actor));
          tmp_actor_ptr = (tmp_actor_ptr -> next);
        }

            if (*mode == 0)
              break;

            else
              continue;


        // else
        //   printf("잘못된 데이터 형식입니다\n");
      }

      fclose(optr);
    }


  void add_actor (FILE *optr, struct actor *actor_ptr) {
    scan_serial_number_a(optr, actor_ptr); // serial_number
    scan_title_a(optr, actor_ptr); // actor_name
    scan_sex_a(optr, actor_ptr); // new one
    scan_birth_a(optr, actor_ptr); // birth
    scan_title_a(optr, actor_ptr); //title
    printf("********************\n  ");
  }


  void scan_serial_number_a(FILE *optr, struct actor *actor_ptr) {
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
    (actor_ptr -> serial_number) = atoi(tmp_name);
    printf("2:%d\n",(actor_ptr -> serial_number));
  }

  void scan_name_a(FILE *optr, struct  actor *actor_ptr){
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
    (actor_ptr->name) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
    strcpy((actor_ptr->name),tmp_name);
    printf("3:%s\n", actor_ptr->name);
  }


  void scan_sex_a (FILE *optr, struct actor *actor_ptr){
    char *tmp_name;
    tmp_name = malloc(1*MAX_TMP);
    scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
    (actor_ptr -> sex) = *tmp_name;
    printf("2:%c\n",(actor_ptr -> sex));
  }


  void scan_birth_a(FILE *optr,struct actor * actor_ptr){
    char *tmp_birth;
    tmp_birth = malloc(1*MAX_TMP);
    scan_word(optr, tmp_birth);
    (actor_ptr->birth) = malloc ((strlen(tmp_birth)+1));
    strcpy((actor_ptr->birth),tmp_birth);
    printf("4:%s\n", actor_ptr->birth);
  }

  void scan_title_a(FILE *optr, struct actor *actor_ptr){

    (actor_ptr->movie_a) = malloc (sizeof(struct movie_in_actor)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
     actor_ptr->movie_a->next = 0;
    struct movie_in_actor *tmp_movie_ptr;
    tmp_movie_ptr = actor_ptr->movie_a;

    char *tmp_str;
    int flag = 1;
    tmp_str = malloc(4*MAX_TMP);
    scan_word(optr, tmp_str);
    printf("point : %s\n", tmp_str);

    while ((flag = str_devider(tmp_str)) != 0) {

      if (*tmp_str == 0)
        break;

      char *tmp_movie;
      tmp_movie = malloc (flag + 1);
      for (int i = 0; i< flag ; i++){
        *(tmp_movie + i) = *(tmp_str + i);
      }
      tmp_str = tmp_str + flag + 1;

      (tmp_movie_ptr->name) = malloc (flag + 1);
      strcpy((tmp_movie_ptr->name), tmp_movie);
      (tmp_movie_ptr->next) = malloc (sizeof(struct actor_in_movie));
      printf("8:%s\n", tmp_movie_ptr->name);
      tmp_movie_ptr = tmp_movie_ptr -> next;

    }
  }




int main () {
  struct main_struct_ptr *data_ptr; // 저장될 모든 데이터들
  data_ptr = malloc(sizeof(struct main_struct_ptr));
  get_data(data_ptr); // 파일 읽고, 정보저장
  // printf("%s", ((data_ptr->movie_ptr)->title));
}
