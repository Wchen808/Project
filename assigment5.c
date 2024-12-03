#include <stdio.h>
#include <stdlib.h>

// Define student structure to hold individual student data
typedef struct {
    char name[50];      // Student's name
    float assignment;   // Assignment score
    float midterm;      // Midterm exam score
    float final;        // Final exam score
    float percentage;   // Calculated semester percentage
    char grade;         // Letter grade
} Student;

// Function to calculate semester percentage and letter grade
void calculateGrades(Student* s) {
    // Calculate weighted percentage
    s->percentage = 0.4 * s->assignment + 0.3 * s->midterm + 0.3 * s->final;

    // Determine letter grade based on percentage
    s->grade = (s->percentage >= 90) ? 'A' :
               (s->percentage >= 85) ? 'B' :
               (s->percentage >= 80) ? 'B' :
               (s->percentage >= 75) ? 'C' :
               (s->percentage >= 70) ? 'C' :
               (s->percentage >= 60) ? 'D' : 'F';
}

int main() {
    // Open input file for reading and output file for writing
    FILE *inFile = fopen("students.csv", "r");
    FILE *outFile = fopen("final.txt", "w");

    // Check if files are opened successfully
    if (!inFile || !outFile) {
        printf("Error: Unable to open file\n");
        return 1;
    }

    Student students[100];       // Array to store data for up to 100 students
    int total = 0;               // Total number of students
    int gradeCounts[7] = {0};    // Counters for grades (A, B+, B, C+, C, D, F)
    float totalAssign = 0, totalMidterm = 0, totalFinal = 0; // Sums for averages

    // Read data from the input file
    while (fscanf(inFile, "%[^,],%f,%f,%f\n", 
                  students[total].name, 
                  &students[total].assignment, 
                  &students[total].midterm, 
                  &students[total].final) != EOF) {
        // Calculate percentage and grade for each student
        calculateGrades(&students[total]);

        // Accumulate totals for averages
        totalAssign += students[total].assignment;
        totalMidterm += students[total].midterm;
        totalFinal += students[total].final;

        // Count grades
        gradeCounts[students[total].grade == 'A' ? 0 :
                    students[total].grade == 'B' ? 1 :
                    students[total].grade == 'C' ? 3 :
                    students[total].grade == 'D' ? 5 : 6]++;

        total++; // Increment student count
    }

    // Calculate averages
    float avgAssign = totalAssign / total;   // Average assignment score
    float avgMidterm = totalMidterm / total; // Average midterm score
    float avgFinal = totalFinal / total;     // Average final score

    // Write results to the output file
    fprintf(outFile, "Name\t\tPercentage\tGrade\n");
    for (int i = 0; i < total; i++) {
        fprintf(outFile, "%s\t\t%.2f\t\t%c\n", 
                students[i].name, 
                students[i].percentage, 
                students[i].grade);
    }

    // Write summary statistics
    fprintf(outFile, "\nTotal Students: %d\n", total);
    fprintf(outFile, "Average Assignment: %.2f\nAverage Midterm: %.2f\nAverage Final: %.2f\n", 
            avgAssign, avgMidterm, avgFinal);
    fprintf(outFile, "Grades: A:%d, B:%d, C:%d, D:%d, F:%d\n", 
            gradeCounts[0], gradeCounts[1], gradeCounts[3], gradeCounts[5], gradeCounts[6]);

    // Close files
    fclose(inFile);
    fclose(outFile);
    return 0;
}
