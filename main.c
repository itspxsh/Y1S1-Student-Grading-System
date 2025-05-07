#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> // for system() function

#define MAX_ITEMS 10
#define MAX_BAR_HEIGHT 20
#define MAX_LABEL_LENGTH 10
#define MIN_BAR_HEIGHT 2

// ANSI color codes
#define COLOR_RESET "\x1b[0m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_BRIGHTGREEN "\x1b[92m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BRIGHTRED "\x1b[91m"
#define COLOR_RED "\x1b[31m"

#define MAX_STUDENTS 100 // ประกาศค่าให้ใช้งานยาว ๆ

typedef struct // ประกาศ datatype ใหม่ (ประกาศstructure) ไว้เก็บข้อมูลนักเรียนคือ ชื่อ คะแนน เกรดรายวิชา เกรดเฉลี่ย
{
    char name[50];     // name
    float scores[8];   // subject
    char grades[8][3]; // A, B+, B, ...
    float gpax;        // 4.0, 3.9
} Student;             // ชื่อ datatypeว่า Student

Student students[MAX_STUDENTS]; // ประกาศตัวแปร student datatype is structure Student
int student_count = 0;          // ตัวแปร count เอาไว้นับจำนวนนักเรียน ทั้งบอก index ตัวแปร และตรวจสอบว่านักเรียนปัจจุบันเกิน max รึยัง

const char *calculate_grade(float score) // ฟังก์ชันประกาศเกรด คือรับค่าคะแนนมาว่าคะแนนนักเรียนคือเท่าไหร่ แล้ว return ค่าออกมาเป็น char คือเกรดที่ได้
{
    if (score >= 80.0)
        return "A";
    else if (score >= 75.0)
        return "B+";
    else if (score >= 70.0)
        return "B";
    else if (score >= 65.0)
        return "C+";
    else if (score >= 60.0)
        return "C";
    else if (score >= 55.0)
        return "D+";
    else if (score >= 50.0)
        return "D";
    else
        return "F";
}

float grade_to_point(const char *grade) // บอกว่าเกรดอะไรได้อะไร
{
    if (strcmp(grade, "A") == 0)
        return 4.0;
    else if (strcmp(grade, "B+") == 0)
        return 3.5;
    else if (strcmp(grade, "B") == 0)
        return 3.0;
    else if (strcmp(grade, "C+") == 0)
        return 2.5;
    else if (strcmp(grade, "C") == 0)
        return 2.0;
    else if (strcmp(grade, "D+") == 0)
        return 1.5;
    else if (strcmp(grade, "D") == 0)
        return 1.0;
    else
        return 0.0;
}

void add_student() // ฟังก์ชันที่เพิ่มชื่อนักเรียน
{
    if (student_count < MAX_STUDENTS) // ถ้าจำนวนนักเรียนปัจจุบันยังน้อยกว่า Max ก็คือ 100 ก็ให้เข้าไปเพิ่มจำนวนนักเรียนได้
    {
        char name[50];
        float scores[8];
        float total_points = 0.0;
        int duplicated = 0;
        do
        {
            duplicated = 0;
            printf("Enter name of student: ");
            getchar();             // This will clear the newline left by the previous scanf
            scanf("%[^\n]", name); // พิมพ์ชื่อนักเรียนที่จะเพิ่มข้อมูล
            for (int i = 0; i < student_count; i++)
            {
                if (strcmp(students[i].name, name) == 0) //ถ้าชื่อที่จะใส่ มีอยู่ในข้อมูลก่อนแล้ว จะใส่ไม่ได้
                {
                    printf("Student already exists in the data.\n\n");
                    duplicated = 1;
                }
            }
            if (duplicated == 1)
            {
                continue;
            }
            else
            {
                break;
            }
        } while (1);

        for (int i = 0; i < 8; i++) // วนรับคะแนน 8 วิชา ถ้าผู้ใช้งานเกรียนกรอกติดลบหรือเกินกว่าร้อย จะแจ้งให้กรอกใหม่
        {
            do
            {
                printf("Enter Score %d (0-100): ", i + 1);
                scanf("%f", &scores[i]);
                if (scores[i] < 0 || scores[i] > 100)
                {
                    printf("Invalid score. Please enter a value between 0 and 100.\n");
                }
            } while (scores[i] < 0 || scores[i] > 100); // loop do วน แต่จะเพิ่มเรื่อย ๆ จน i เป็น 8 แล้วหยุดเองอยู่ดี
        }
        // เก็บค่าเข้าตัวแปร student
        strcpy(students[student_count].name, name); // เอาชื่อนักเรียนที่เก็บไว้ใน name มา copy ไว้ในstudent
        for (int i = 0; i < 8; i++)                 // เอาคะแนนมาเก็บไว้ใน student
        {
            students[student_count].scores[i] = scores[i];                         // เก็บเข้าไปใน score ใน structure student
            strcpy(students[student_count].grades[i], calculate_grade(scores[i])); // copy grade เข้าตัวแปรเกรด โดยใช้ฟังก์ชันประกาศเกรด โดยรับค่าที่เป็นคะแนนนักเรียนไป
            total_points += grade_to_point(students[student_count].grades[i]);     // total point บวกเพิ่มไปทีละวิชา โดยใช้ฟังก์ชัน grade to point เพื่อแปลงตัวเกรดกลายเป็นเกรดแบบคะแนน จะได้ผลรวมทั้งหมด
        }

        students[student_count].gpax = total_points / 8; // เอาผลรวมเกรดมาหาร 8 ที่เป็นจำนวนวิชา แล้วใส่ค่าไปในตัวแปร gpax ของ structure student (ตัวที่ count)
        student_count++;                                 // พอเพิ่มนักเรียนเสร็จก็เพิ่มจำนวนนักเรียน
    }
    else
    {
        printf("Student limit reached.\n"); // จากการตรวจสอบว่า student_count เกินจำนวน student_Max รึยัง ถ้าเกินแล้วให้ประกาศเตือน ว่าเพิ่มไม่ได้
    }
}

void import_student_data()
{ // ฟังก์ชันเปิดไฟล์ -เอาไว้ทำไร
    char filename[100];
    printf("Enter the file name to import data from: ");
    scanf("%s", filename); // รับชื่อไฟล์มาเพื่อที่จะเปิด

    FILE *file = fopen(filename, "r"); // ประกาศตัวแปร file เพื่อทำการเปิดไฟล์ และใช้โหมดอ่าน คืออ่านค่ามาใช้งาน
    if (file == NULL)
    {
        printf("Error: Could not open file %s.\n", filename); // แต่ถ้า file ว่าง ไม่มีข้อมูลในนั้น ก็จะบอกว่าเปิดไม่ได้
        return;
    }

    getchar();
    while (fscanf(file, " Name: %[^\n]", students[student_count].name) == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            int score_num;
            char grade_label[10];
            if (fscanf(file, " Score%d: %f - Grade: %*s", &score_num, &students[student_count].scores[i]) != 2)
            {
                printf("Error reading scores from file.\n");
                fclose(file);
                return;
            }
            strcpy(students[student_count].grades[i], calculate_grade(students[student_count].scores[i]));
        }
        if (fscanf(file, " GPAX: %f", &students[student_count].gpax) != 1)
        {
            printf("Error reading GPAX from file.\n");
            fclose(file);
            return;
        }
        student_count++;
        if (student_count >= MAX_STUDENTS)
        {
            printf("Warning: Maximum student limit reached; additional data will not be loaded.\n");
            break; // ถ้ารายชื่อนักเรียนในไฟล์มีจำนวนเกิด Max ที่เราตั้งไว้ ให้ประกาศว่า load ไม่ได้
        }
    }
    fclose(file);
    printf("Data imported successfully from %s.\n", filename); // บอกว่าเอาไฟล์เข้ามาใช้งานได้แล้ว (เอาข้อมูลในไฟล์เข้ามาใส่ student?)
}

void adjust_student_data()
{ // ฟังก์ชันแก้ไขข้อมูลนักเรียน
    char name[50];
    printf("Enter name of student to adjust: ");
    getchar();
    scanf("%[^\n]", name); // ป้อนชื่อนักเรียนที่อยากแก้

    for (int i = 0; i < student_count; i++)
    { // วนตามจำนวนนักเรียน (เพื่อตามหานักเรียนที่ต้องการแก้ไข)
        if (strcmp(students[i].name, name) == 0)
        {                                                         // หาชื่อนักเรียนที่ต้องการแก้ไขใน student ถ้าเจอให้ทำต่อ
            printf("Adjusting data for %s:\n", students[i].name); // เจอข้อมูลแล้วให้บอกว่า เออ จะแก้ข้อมูลให้เด็กคนนี้นะ
            float total_points = 0.0;                             // ประกาศตัวแปร total point เอาไว้รวมเกรด
            for (int j = 0; j < 8; j++)
            { // วนรับค่าเกรดใหม่ (แก้ไขข้อมูล)
                do
                {
                    printf("Enter new Score %d (0-100): ", j + 1);
                    scanf("%f", &students[i].scores[j]); // รับค่าคะแนนใหม่เข้าตัวแปร student
                    if (students[i].scores[j] < 0 || students[i].scores[j] > 100)
                    { // เตือนขอบเขตคะแนนที่กรอกได้
                        printf("Invalid score. Please enter a value between 0 and 100.\n");
                    }
                } while (students[i].scores[j] < 0 || students[i].scores[j] > 100); // ถ้าตัวคะแนนที่กรอกมายังไม่สมเหตุสมผลให้กลับขึ้นไปทำใหม่ โดยที่ j ก็ไม่ได้เพิ่ม เป็นการทำซ้ำ index เดิม แต่ถ้าข้อมูลมันถูกคือคะแนนสมเหตุสมผล มันก็จะหลุด loop do แล้วทำหารเพิ่ม j ใน loop for เพื่อทำการเก็บคะแนนในวิชาต่อไป
                strcpy(students[i].grades[j], calculate_grade(students[i].scores[j])); // รับค่าเกรด
                total_points += grade_to_point(students[i].grades[j]);                 // step เดิมเหมือนตอนรับค่านักเรียนใหม่คือการคำนวณเกรด
            }
            students[i].gpax = total_points / 8;
            printf("Data for %s updated successfully.\n", name);
            return;
        }
    }
    printf("Student with name %s not found.\n", name); // ถ้าวนจนครบแล้วก็ยังไม่เจอชื่อนักเรียนที่ตรวจสอบใน if ก็ให้บอกว่าไม่เจอชื่อนักเรียน
}

void show_student_data()
{ // ฟังก์ชันไว้แสดงรายชื่อนักเรียน
    char name[50];
    printf("Enter name of student to view data: ");
    getchar();
    scanf("%[^\n]", name); // กรอกชื่อนักเรียนที่อยากรู้ข้อมูล

    for (int i = 0; i < student_count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {                                                 // วนหาชื่อนักเรียนที่ต้องการดูข้อมูล
            printf("\nData for %s:\n", students[i].name); // บอกว่านี่คือข้อมูลของใคร
            for (int j = 0; j < 8; j++)
            {
                printf("Score%d: %.2f - Grade: %s\n", j + 1, students[i].scores[j], students[i].grades[j]); // แสดงคะแนนแหละเกรดแต่ละวิชา 8 วิชา
            }
            printf("GPAX: %.2f\n", students[i].gpax); // บอกเกรดรวม
            return;
        }
    }
    printf("Student with name %s not found.\n", name); // ถ้าหาชื่อนักเรียนที่อยากดูข้อมูลไม่เจอ
}

void calculate_min_scores()
{ // ฟังก์ชันสำหรับหาคะแนนที่น้อยที่สุดของแต่ละวิชา
    if (student_count == 0)
    { // ถ้ายังไม่มีข้อมูลนักเรียนให้บอกว่ามันไม่มี
        printf("No student data available.\n");
        return;
    }
    float min_scores[8];
    for (int j = 0; j < 8; j++)
    { // เอาคะแนนทุกวิชาของนักเรียนคนแรก มายัดใส่ให้เป็นค่า min ไปก่อน
        min_scores[j] = students[0].scores[j];
    }
    for (int i = 1; i < student_count; i++)
    { // วนตามจำนวนนักเรียน เพื่อตามหาคะแนนของคนที่น้อย
        for (int j = 0; j < 8; j++)
        {
            if (students[i].scores[j] < min_scores[j])
            { // ตรวจนักเรียนที่ละคนว่าคะแนนแต่ละวิชา น้อยกว่าของคนแรกมั้ย ถ้าน้อยกว่า ให้ min_score ปัจจุบันเป็นคะแนนของคนนนั้น ๆ ไป
                min_scores[j] = students[i].scores[j];
            }
        }
    }
    printf("\nMinimum Scores for Each Subject:\n"); // พิมพ์คะแนนที่น้อยที่สุดของแต่ละวิชา
    for (int j = 0; j < 8; j++)
    {
        printf("Min of Score %d: %.2f\n", j + 1, min_scores[j]);
    }
}

void calculate_max_scores()
{ // ฟังก์ชันสำหรับหาค่าคะแนนที่มากที่มาดที่สุดของแต่ละวิชา
    if (student_count == 0)
    {
        printf("No student data available.\n");
        return;
    }
    float max_scores[8];
    for (int j = 0; j < 8; j++)
    {
        max_scores[j] = students[0].scores[j];
    }
    for (int i = 1; i < student_count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (students[i].scores[j] > max_scores[j])
            {
                max_scores[j] = students[i].scores[j];
            }
        }
    }
    printf("\nMaximum Scores for Each Subject:\n");
    for (int j = 0; j < 8; j++)
    {
        printf("Max of Score %d: %.2f\n", j + 1, max_scores[j]);
    }
}

void calculate_mean_scores(float mean_scores[])
{ // ฟังก์ชันสำหรับคำนวณค่าเฉลี่ยคะแนนของแต่ละวิชา
    if (student_count == 0)
    {
        printf("No student data available.\n");
        return;
    }
    float sum_scores[8] = {0}; // ประกาศตัวแปรเก็บผลรวมคะแนนแต่ละวิชา (มี 8 วิชา)
    for (int i = 0; i < student_count; i++)
    { // วนนักเรียนทุกคน
        for (int j = 0; j < 8; j++)
        {
            sum_scores[j] += students[i].scores[j]; // วนไปทุกวิชาของนักเรียนทีละคน
        }
    }
    printf("\nMean Scores for Each Subject:\n"); // แสดงค่าเฉลี่ยคะแนนของแต่ละวิชา
    for (int j = 0; j < 8; j++)
    {
        mean_scores[j] = sum_scores[j] / student_count;
        printf("Mean of Score %d: %.2f\n", j + 1, mean_scores[j]);
    }
}

void calculate_standard_deviation_scores(float mean_scores[])
{ // คำนวณค่า SD ของแต่ละวิชา
    if (student_count == 0)
    {
        printf("No student data available.\n");
        return;
    }
    float sum_squared_diff[8] = {0};
    float sd_scores[8]; // ตัวแปรเก็บค่า sd 8 วิชา
    for (int i = 0; i < student_count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            float diff = students[i].scores[j] - mean_scores[j];
            sum_squared_diff[j] += diff * diff; // คิดสูตรของ ผลรวมmean
        }
    }
    printf("\nStandard Deviation for Each Subject:\n"); // คิดค่า sd ตามสูตรและแสดงออกมา
    for (int j = 0; j < 8; j++)
    {
        sd_scores[j] = sqrt(sum_squared_diff[j] / student_count);
        printf("SD of Score %d: %.2f\n", j + 1, sd_scores[j]);
    }
}

void print_all_records_to_file()
{                                                   // เก็บข้อมูลเข้าไปใน file
    FILE *file = fopen("student_records.txt", "w"); // declare file เปิดไฟล์ขึ้นมาเพื่อเขียน
    if (file == NULL)
    {
        printf("Error opening file.\n"); // file ว่าง แล้วจบเลย
        return;
    }

    for (int i = 0; i < student_count; i++)
    { // วนเขียนข้อมูลใน file ตามข้อมูลที่มีอยู่ใน student ตามจำนวน count ที่มี
        fprintf(file, "Name: %s\n", students[i].name);
        for (int j = 0; j < 8; j++)
        {                                                                                                      // วนเขียนคะแนน 8 วิชา
            fprintf(file, "Score%d: %.2f - Grade: %s\n", j + 1, students[i].scores[j], students[i].grades[j]); // write to file that what is score what is grade
        }
        fprintf(file, "GPAX: %.2f\n\n", students[i].gpax);
    }

    fclose(file);
    printf("All records saved to student_records.txt\n"); // ข้อมูลอยู่ในไฟล์เรียบร้อยแล้ว
}

const char *BAR_STYLES = "█";

typedef struct
{
    char label[MAX_LABEL_LENGTH]; // ขนาดของ chart
    int value;
    const char *color;
} BarData; // ประกาศข้อมูลประเภท Bardata เก็บ label value และสี

void clearScreen(void)
{
    printf("\x1b[2J\x1b[H");
}
void printVerticalBarChart(BarData data[], int numItems, const char *title); // fix implicit declaration warnings

void calculate_chart()
{ // คำนวณchart
    if (student_count == 0)
    {
        printf("No student data available.\n");
        return; // ยังไม่มีข้อมูลนักเรียน
    }

    clearScreen();

    // Ask user which subject to analyze
    int subject_choice;
    printf("\nWhich subject would you like to analyze?\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d. Subject %d\n", i + 1, i + 1);
    }
    printf("9. All Subjects Combined\n");

    do
    {
        printf("\nEnter your choice (1-9): ");
        if (scanf("%d", &subject_choice) != 1 || subject_choice < 1 || subject_choice > 9)
        { // The comparison ensures the input is valid ห้ามผู้ใช้กรอกอย่างอื่นที่ไม่ใช่ตัวเลข
            printf("Invalid input. Please enter a number between 1 and 9.\n");
            while (getchar() != '\n')
                ; // Clear input buffer
            continue;
        }
        break;
    } while (1);

    // Initialize grade counters
    int grade_counts[8] = {0}; // A, B+, B, C+, C, D+, D, F

    if (subject_choice == 9)
    {
        // For all subjects combined, count total occurrences of each grade
        for (int i = 0; i < student_count; i++)
        {
            for (int j = 0; j < 8; j++)
            { // Loop through each subject
                const char *grade = students[i].grades[j];
                if (strcmp(grade, "A") == 0)
                    grade_counts[0]++;
                else if (strcmp(grade, "B+") == 0)
                    grade_counts[1]++;
                else if (strcmp(grade, "B") == 0)
                    grade_counts[2]++;
                else if (strcmp(grade, "C+") == 0)
                    grade_counts[3]++;
                else if (strcmp(grade, "C") == 0)
                    grade_counts[4]++;
                else if (strcmp(grade, "D+") == 0)
                    grade_counts[5]++;
                else if (strcmp(grade, "D") == 0)
                    grade_counts[6]++;
                else if (strcmp(grade, "F") == 0)
                    grade_counts[7]++;
            }
        }
    }
    else
    {
        // Count grades for specific subject
        int subject_index = subject_choice - 1;
        for (int i = 0; i < student_count; i++)
        {
            if (strcmp(students[i].grades[subject_index], "A") == 0)
                grade_counts[0]++;
            else if (strcmp(students[i].grades[subject_index], "B+") == 0)
                grade_counts[1]++;
            else if (strcmp(students[i].grades[subject_index], "B") == 0)
                grade_counts[2]++;
            else if (strcmp(students[i].grades[subject_index], "C+") == 0)
                grade_counts[3]++;
            else if (strcmp(students[i].grades[subject_index], "C") == 0)
                grade_counts[4]++;
            else if (strcmp(students[i].grades[subject_index], "D+") == 0)
                grade_counts[5]++;
            else if (strcmp(students[i].grades[subject_index], "D") == 0)
                grade_counts[6]++;
            else if (strcmp(students[i].grades[subject_index], "F") == 0)
                grade_counts[7]++;
        }
    }

    BarData data[] = {
        {"A ", grade_counts[0], COLOR_MAGENTA},
        {"B+", grade_counts[1], COLOR_BLUE},
        {"B ", grade_counts[2], COLOR_CYAN},
        {"C+", grade_counts[3], COLOR_GREEN},
        {"C ", grade_counts[4], COLOR_BRIGHTGREEN},
        {"D+", grade_counts[5], COLOR_YELLOW},
        {"D ", grade_counts[6], COLOR_BRIGHTRED},
        {"F ", grade_counts[7], COLOR_RED}};
    int numItems = sizeof(data) / sizeof(data[0]);

    // Create appropriate title based on choice
    char title[100];
    if (subject_choice == 9)
    {
        snprintf(title, sizeof(title), "Overall Grade Distribution (All Subjects Combined)");
    }
    else
    {
        snprintf(title, sizeof(title), "Grade Distribution Chart (Subject %d)", subject_choice);
    }

    printVerticalBarChart(data, numItems, title);

    // Calculate total grades and statistics
    int totalGrades = 0;
    for (int i = 0; i < 8; i++)
    {
        totalGrades += grade_counts[i];
    }

    if (subject_choice == 9)
    {
        printf("\nTotal number of grades across all subjects: %d\n", totalGrades);
        printf("Total number of students: %d\n", student_count);

        // Calculate overall statistics
        float total_score = 0;
        float max_score = 0;
        float min_score = 100;

        // Track best and worst performing subjects
        float subject_averages[8] = {0};
        int best_subject = 0;
        int worst_subject = 0;

        // Calculate average for each subject
        for (int j = 0; j < 8; j++)
        {
            float subject_total = 0;
            for (int i = 0; i < student_count; i++)
            {
                float score = students[i].scores[j];
                subject_total += score;

                if (score > max_score)
                    max_score = score;
                if (score < min_score)
                    min_score = score;
            }
            subject_averages[j] = subject_total / student_count;

            if (subject_averages[j] > subject_averages[best_subject])
            {
                best_subject = j;
            }
            if (subject_averages[j] < subject_averages[worst_subject])
            {
                worst_subject = j;
            }
        }

        // Calculate overall average
        float overall_avg = 0;
        for (int j = 0; j < 8; j++)
        {
            overall_avg += subject_averages[j];
        }
        overall_avg /= 8;

        printf("\nOverall Statistics (All Subjects):\n");
        printf("Average Score across all subjects: %.2f\n", overall_avg);
        printf("Highest Individual Score: %.2f\n", max_score);
        printf("Lowest Individual Score: %.2f\n", min_score);
        printf("Best Performing Subject: Subject %d (Average: %.2f)\n", best_subject + 1, subject_averages[best_subject]);
        printf("Most Challenging Subject: Subject %d (Average: %.2f)\n", worst_subject + 1, subject_averages[worst_subject]);
        printf("\nNote: This view shows the distribution of ALL grades across ALL subjects combined.\n");
        printf("Each student contributes 8 grades to this distribution (one for each subject).\n");
    }
    else
    {
        printf("\nSubject %d Statistics:\n", subject_choice);
        printf("Total number of students: %d\n", totalGrades);

        // Calculate subject-specific statistics
        float subject_avg = 0;
        float max_score = students[0].scores[subject_choice - 1];
        float min_score = students[0].scores[subject_choice - 1];

        for (int i = 0; i < student_count; i++)
        {
            float score = students[i].scores[subject_choice - 1];
            subject_avg += score;

            if (score > max_score)
                max_score = score;
            if (score < min_score)
                min_score = score;
        }
        subject_avg /= student_count;

        printf("Average Score: %.2f\n", subject_avg);
        printf("Highest Score: %.2f\n", max_score);
        printf("Lowest Score: %.2f\n", min_score);
    }
}

// Function to calculate the scaled height of each bar
int calculateBarHeight(int value, int maxValue, int maxBarHeight)
{ // คำนวณความสูงของแท่งกราฟิก
    return (value * maxBarHeight) / maxValue;
}

void printVerticalBarChart(BarData data[], int numItems, const char *title)
{ // รับข้อมูล3ส่วน
    if (numItems <= 0 || numItems > MAX_ITEMS)
    { // ตรวจสอบว่าจำนวนไอเทมน้อยกว่าหรือเท่ากับ 0 หรือไม่ ซึ่งถือว่าเป็นค่าที่ไม่ถูกต้อง
        printf("Error: Invalid number of items (1-%d allowed)\n", MAX_ITEMS);
        return;
    }

    // Find the maximum number of students (max value) and calculate total students
    int maxStudents = 0;
    int totalStudents = 0;
    for (int i = 0; i < numItems; i++)
    {
        totalStudents += data[i].value;
        if (data[i].value > maxStudents)
        { // ตรวจสอบว่าค่า data[i].value มากกว่าค่า maxStudents หรือไม่
            maxStudents = data[i].value;
        }
    }

    // Print the title of the chart
    printf("\n%s\n", title);
    for (int i = 0; i < strlen(title); i++)
        printf("=");
    printf("\n\n");

    // Print the vertical axis and bars
    printf("Number of Students \n\n");
    for (int height = maxStudents; height >= 0; height -= (maxStudents / MAX_BAR_HEIGHT + 1))
    {
        // Print the student count on the left
        printf("%3d │", height);

        // For each item, print the bar at the corresponding height level
        for (int i = 0; i < numItems; i++)
        {
            int barHeight = calculateBarHeight(data[i].value, maxStudents, MAX_BAR_HEIGHT); // เรียกใช้ฟังก์ชัน calculateBarHeight เพื่อคำนวณความสูงของแท่งกราฟิกสำหรับข้อมูลชิ้นที่ i
            if (height <= data[i].value)
            {
                // Print the colored bar if it reaches this height
                printf("%s", data[i].color);
                printf(" %s", BAR_STYLES);
                printf("  %s", COLOR_RESET);
            }
            else
            {
                printf("    ");
            }
        }
        printf("\n");
    }

    // Printing the separator line for the chart
    printf("    ├");
    for (int i = 0; i < numItems; i++)
    {
        printf("────");
    }
    printf("\t Grade Levels\n");

    // Printing the labels for the grades at the bottom
    printf("      ");
    for (int i = 0; i < numItems; i++)
    {
        printf("%-4s", data[i].label);
    }
    printf("\n");

    // Printing the detailed grade distribution information with percentages
    printf("\nGrade Distribution:\n");
    for (int i = 0; i < numItems; i++)
    {
        float percentage = ((float)data[i].value / totalStudents) * 100;
        printf("%s%s%s: %d grades (%.1f%%)\n",
               data[i].color,
               data[i].label,
               COLOR_RESET,
               data[i].value,
               percentage);
    }
}

int main()
{
    system("chcp 65001 > nul"); // Set console to UTF-8 code page and don't display it

    int choice;
    float mean_scores[8];

    while (1)
    {
        printf("\nMenu: (type 1-10)\n");
        printf("1.\tAdd student data\n");
        printf("2.\tAdjust student data\n");
        printf("3.\tShow student data\n");
        printf("4.\tShow max score of each subject\n");
        printf("5.\tShow min score of each subject\n");
        printf("6.\tShow mean of each subject\n");
        printf("7.\tShow SD of each subject\n");
        printf("8.\tShow grade distribution chart\n");
        printf("9.\tPrint all records as grader and save to a text file\n");
        printf("10.\tImport student data from a file\n");
        printf("11.\tExit the program\n");
        printf("Select menu: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice. Please type a number between 1 and 10.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            adjust_student_data();
            break;
        case 3:
            show_student_data();
            break;
        case 4:
            calculate_max_scores();
            break;
        case 5:
            calculate_min_scores();
            break;
        case 6:
            calculate_mean_scores(mean_scores);
            break;
        case 7:
            calculate_standard_deviation_scores(mean_scores);
            break;
        case 8:
            calculate_chart();
            break;
        case 9:
            print_all_records_to_file();
            break;
        case 10:
            import_student_data();
            break;
        case 11:
            printf("Exiting program.\n");
            return 0;
        default:
            printf("Invalid choice. Please type a number between 1 and 10.\n");
        }
    }

    return 0;
}
