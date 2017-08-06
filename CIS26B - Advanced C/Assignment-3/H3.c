/**
CIS 26B - Advanced C Programming
Homework #3:
Hashing to a file and using advanced string manipulation functions.

This program allows additions to, deletions from, or displays of database records in a student database.

NAME: Rashmi Baheti
IDE: Visual Studio
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  //exit
#include <ctype.h>   // isdigit

#define FILENAME "input.txt"
#define BINARYFILENAME "binary_file"
#define TABSIZE 40
#define BUCKETSIZE 3 // structs per bucket

typedef struct student_record STUDENT_RECORD;
struct student_record
{
  char student_id[5];
  double gpa;
  char first_name[50];
  char last_name[50];
};

// Fuction prototypes.
long hash(int key, int size);
void readInputFile(char* input_filename, FILE *fp);
void readUserInputFile(char* input_filename, FILE *fp);
FILE *create_hash_file(char *filename);
void insert_record(STUDENT_RECORD stu_record, long address, FILE *fp);
int search_record(STUDENT_RECORD stu_record, long address, FILE *fp);
void programMenu(FILE *fp);
void delete_record(STUDENT_RECORD stu_record, long address, FILE *fp);

int main(int argc, char *argv[])
{
  FILE *fp;
  fp = create_hash_file(BINARYFILENAME);

  char input_filename[100] = "FILENAME";
  if (argc > 1) {
    strcpy(input_filename, argv[1]);
  }
  readInputFile(input_filename, fp);
  programMenu(fp);

  getchar();
  return 0;
}

/* ====================================================
programMenu presents menu to the user to let the user
read or modify the database.
*/
void programMenu(FILE *fp) {
  while (1) {
    printf("\nPlease choose one of the following:\n");
    printf("A. Search (by id)\n");
    printf("B. Delete (by id)\n");
    printf("C. Insert from file\n");
    printf("D. Insert from keyboard\n");
    printf("E. Quit\n");

    char inputStr[100];
    while (1) {
      gets(inputStr);
      const int strlength = strlen(inputStr);
      if (strlength > 1) {
        printf("Please enter only 1 character A through E\n");
        continue;
      }

      int inputChar = toupper(inputStr[0]);
      if (inputChar < 'A' || inputChar > 'E') {
        printf("Please enter a character A through E\n");
        continue;
      }
      break;  // input is valid now.
    }

    int inputChar = toupper(inputStr[0]);
    switch (inputChar) {
    case 'A':
    {
      printf("\nPlease enter a student id to search: ");
      char id[100];
      scanf("%s", id);
      STUDENT_RECORD temp_record;
      strcpy(temp_record.student_id, strtok(id, " \t\n"));
      long address = hash(temp_record.student_id, TABSIZE);
      if (search_record(temp_record, address, fp) == 0) {
        printf("Student with id %s not found in the database.\n", temp_record.student_id);
      }
    }
    break;

    case 'B':
    {
      printf("\nPlease enter a student id you want to delete: ");
      char id[100];
      scanf("%s", id);
      STUDENT_RECORD temp_record;
      strcpy(temp_record.student_id, strtok(id, " \t\n"));
      long address = hash(temp_record.student_id, TABSIZE);
      delete_record(temp_record, address, fp);
    }
    break;

    case 'C':
    {
      char input_filename[100];
      printf("Please enter your file name: ");
      gets(input_filename);
      readUserInputFile(input_filename, fp);
    }
    break;

    case 'D': {
      char input_string[100];
      char *id;
      char *last_name;
      char *first_name;
      char *gpa;
      int invalid_input = 1;
      double gpa_score;

      while (invalid_input) {
        invalid_input = 0;
        printf("\nPlease enter a student details in following sequence:\n");
        printf("student_id,last_name first_name;gpa\n");
        gets(input_string);
        // Parse given string.
        id = strtok(input_string, " ,\t;");
        last_name = strtok(NULL, " ,\t;");
        first_name = strtok(NULL, " ,\t;");
        gpa = strtok(NULL, " ,\t;");

        // Validate student's id.
        if (strlen(id) != 4) {
          printf("\nStudent id should be 4 digit integer. Please enter a valid student record.\n");
          invalid_input = 1;
        }
        else {
          for (int i = 0; i < 4; ++i) {
            int isnum = isdigit(id[i]);
            if (!isnum) {
              printf("\nStudent id should be 4 digit integer. Please enter a valid student record.\n");
              invalid_input = 1;
              break;
            }
          }
        }
        if (invalid_input) {
          continue;
        }

        // Validate student's last name.
        int last_name_length = strlen(last_name);
        for (int i = 0; i < last_name_length; ++i) {
          int isalphabet = isalpha(last_name[i]);
          if (!isalphabet) {
            printf("\nStudent name should be alphabets only. Please enter a valid student record.\n");
            invalid_input = 1;
            break;
          }
          else {
            last_name[i] = toupper(last_name[i]);
          }
        }
        if (invalid_input) {
          continue;
        }


        // Validate student's first name.
        int first_name_length = strlen(first_name);
        for (int i = 0; i < first_name_length; ++i) {
          int isalphabet = isalpha(first_name[i]);
          if (!isalphabet) {
            printf("\nStudent name should be alphabets only. Please enter a valid student record.\n");
            invalid_input = 1;
            break;
          }
          else {
            first_name[i] = toupper(first_name[i]);
          }
        }
        if (invalid_input) {
          continue;
        }

        // Validate student's gpa.
        char *end;
        gpa_score = strtod(gpa, NULL);
        gpa_score = strtod(gpa, &end);
        if (*end != '\0')  {
          printf("GPA is not a number");
          printf("\nStudent gpa should be between 0.0 and 4.0. Please enter a valid student record.\n");
          invalid_input = 1;
        }
        if (gpa_score < 0.0 && gpa_score > 4.0) {
          printf("\nStudent GPA should be between 0.0 and 4.0. Please enter a valid student record.\n");
          invalid_input = 1;
        }

        if (invalid_input) {
          continue;
        }
      }

      STUDENT_RECORD temp_record;
      strcpy(temp_record.student_id, id);
      strcpy(temp_record.last_name, last_name);
      strcpy(temp_record.first_name, first_name);
      temp_record.gpa = gpa_score;
      long address = hash(temp_record.student_id, TABSIZE);
      insert_record(temp_record, address, fp);
      printf("Your recrd has been added to the database.\n");
    }
    break;

    case 'E':
      printf("Exiting now...");
      return;

    default:
      printf("Invalid input\n");
    }
  }
}

/*	========================================================
Read the input file provided by agrv and populate binary file 
with the student records read from the file.
*/
void readInputFile(char* input_filename, FILE *fp) {
  FILE *fpData;
  if ((fpData = fopen(input_filename, "r")) == NULL)
  {
    {
      printf("Error opening %s file for reading\n", input_filename);
      getchar();
      exit(101);
    }
  }
  char ch;
  int i = 0;
  while ((ch = fgetc(fpData)) != EOF)
  {
    STUDENT_RECORD stu_record;
    ungetc(ch, fpData);
    fscanf(fpData, "%[^ ] %lf %[^ ] %s%*c", stu_record.student_id, &stu_record.gpa,
      stu_record.last_name, stu_record.first_name);

    long address = hash(stu_record.student_id, TABSIZE);
    insert_record(stu_record, address, fp);
  }

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing %s!", input_filename);
    exit(201);
  }
}
/*	========================================================
Read the input file provided by the user via menu and 
populate binary file with the student records read from the file.
*/
void readUserInputFile(char* input_filename, FILE *fp) {
  FILE *fpData;
  if ((fpData = fopen(input_filename, "r")) == NULL)
  {
    {
      printf("Error opening %s file for reading\n", input_filename);
      return;
    }
  }
  char ch;
  int i = 0;
  while ((ch = fgetc(fpData)) != EOF)
  {
    STUDENT_RECORD stu_record;
    ungetc(ch, fpData);
    fscanf(fpData, "%[^,],%[^ ] %[^;];%lf%*c", stu_record.student_id,
      stu_record.last_name, stu_record.first_name, &stu_record.gpa);

    long address = hash(stu_record.student_id, TABSIZE);
    insert_record(stu_record, address, fp);
  }

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing %s!", input_filename);
    return;
  }
}

/* ========================================================
Computes index of the hash bucket in which a record of the 
given key should be inserted. 
*/
long hash(char *key, int size)
{
  long address = 0;
  for (; *key != '\0'; key++)
  {
    address += *key * *key * *key;
  }
  return address % size;
}

/********************************************************
 Create an empty binary hash file
*/
FILE *create_hash_file(char *filename)
{
  FILE *fp;
  STUDENT_RECORD hashtable[TABSIZE][BUCKETSIZE] = { "", 0.0, "", "" };

  if ((fp = fopen(filename, "w+b")) == NULL)
  {

    printf("Could not open %s.\n", filename);
    exit(1);
  }

  // check for write errors just to be safe.
  if (fwrite(&hashtable[0][0], sizeof(STUDENT_RECORD), TABSIZE * BUCKETSIZE, fp) < TABSIZE)
  {
    printf("Hash table could not be created. Abort!\n");
    exit(2);
  }

  rewind(fp);
  return fp;
}

/******************************************************
Hashing to Disk: Insert
*/
void insert_record(STUDENT_RECORD stu_record, long address, FILE *fp)
{
  STUDENT_RECORD detect;
  int i;

  int already_exists = search_record(stu_record, address, fp);
  if (already_exists) {
    printf("Student %s already exists in the database. ", stu_record.student_id);
    printf("Entry for this student will not be added to the database.!\n");
    return;
  }

  // go to beginning of hash bucket
  if (fseek(fp, address * BUCKETSIZE * sizeof(STUDENT_RECORD), SEEK_SET) != 0)
  {
    printf("Fatal seek error! Abort!\n");
    exit(4);
  }

  // find first available slot in the bucket.
  for (i = 0; i < BUCKETSIZE; i++)
  {
    fread(&detect, sizeof(STUDENT_RECORD), 1, fp);
    if (*detect.student_id == '\0') // available slot
    {
      int size_of_stu_record = (unsigned)sizeof(STUDENT_RECORD);
      fseek(fp, -1L * size_of_stu_record, SEEK_CUR);
      fwrite(&stu_record, sizeof(STUDENT_RECORD), 1, fp);
      return; // nothing left to do
    }
  }

  // item not inserted!
  printf("Hash table overflow! Entry for student %s will not be added to the database.!\n",
    stu_record.student_id);
}

/******************************************************
Hashing to Disk: Search
*/
int search_record(STUDENT_RECORD stu_record, long address, FILE *fp)
{
  STUDENT_RECORD detect;
  int i;

  if (fseek(fp, address * BUCKETSIZE * sizeof(STUDENT_RECORD), SEEK_SET) != 0)
  {
    printf("Fatal seek error! Abort");
    exit(4);
  }
  // find given record in the bucket.
  for (i = 0; i < BUCKETSIZE; i++)
  {
    fread(&detect, sizeof(STUDENT_RECORD), 1, fp);
    if (strcmp(detect.student_id, stu_record.student_id) == 0) // found it!
    {
      printf("Student with id %s exists in the database.\nStudent name:%s %s GPA:%.1lf\n",
        detect.student_id, detect.last_name, detect.first_name, detect.gpa);
      return 1; // nothing left to do
    }
  }

  // not found
  return 0;
}

/******************************************************
Hashing to Disk: Delete
*/
void delete_record(STUDENT_RECORD stu_record, long address, FILE *fp)
{
  STUDENT_RECORD detect;
  int i;

  if (fseek(fp, address * BUCKETSIZE * sizeof(STUDENT_RECORD), SEEK_SET) != 0)
  {
    printf("Fatal seek error! Abort");
    exit(4);
  }
  // find given record in the bucket.
  for (i = 0; i < BUCKETSIZE; i++)
  {
    fread(&detect, sizeof(STUDENT_RECORD), 1, fp);
    if (strcmp(detect.student_id, stu_record.student_id) == 0) // found it!
    {
      printf("Deleting student with id %s from hash bucket %ld.\nStudent name:%s %s GPA:%.1lf\n",
        detect.student_id, address, detect.last_name, detect.first_name, detect.gpa);
      int size_of_stu_record = (unsigned)sizeof(STUDENT_RECORD);
      fseek(fp, -1L * size_of_stu_record, SEEK_CUR);
      strcpy(detect.student_id, "");
      detect.gpa = 0.0;
      strcpy(detect.last_name, "");
      strcpy(detect.first_name, "");
      fwrite(&detect, sizeof(STUDENT_RECORD), 1, fp);
      return; // nothing left to do
    }
  }

  // not found
  printf("Record with key: %s : not found.\n", stu_record.student_id);
  return;
}


/********************  SAMPLE OUTPUT   **************************

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
a

Please enter a student id to search: 1235
Student with id 1235 exists in the database.
Student name:WILLIAMS MARC GPA:3.2

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
Please enter a character A through E
a

Please enter a student id to search: krjh123
Student with id krjh123 not found in the database.

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
Please enter a character A through E
b

Please enter a student id you want to delete: 1235
Deleting student with id 1235 from hash bucket 17.
Student name:WILLIAMS MARC GPA:3.2

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
Please enter a character A through E
a

Please enter a student id to search: 1235
Student with id 1235 not found in the database.

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
Please enter a character A through E
c
Please enter your file name: user.txt
Hash table overflow! Entry for student 8123 will not be added to the database.!
Student with id 9524 exists in the database.
Student name:ROBINSON YELENA GPA:4.0
Student 9524 already exists in the database. Entry for this student will not be added to the databas
e.!
Hash table overflow! Entry for student 2756 will not be added to the database.!

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
d

Please enter a student details in following sequence:
student_id,last_name first_name;gpa
hejk, kjf krjf;3.2

Student id should be 4 digit integer. Please enter a valid student record.

Please enter a student details in following sequence:
student_id,last_name first_name;gpa
1234,abc111 kjf;3.2

Student name should be alphabets only. Please enter a valid student record.

Please enter a student details in following sequence:
student_id,last_name first_name;gpa
1234,abc xyz;kjf
GPA is not a number
Student gpa should be between 0.0 and 4.0. Please enter a valid student record.

Please enter a student details in following sequence:
student_id,last_name first_name;gpa
1234,abc                xyz;    3.2
Your recrd has been added to the database.

Please choose one of the following:
A. Search (by id)
B. Delete (by id)
C. Insert from file
D. Insert from keyboard
E. Quit
e
Exiting now...

**/