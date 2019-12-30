#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 300
#define FIRST_LINE 1

typedef struct{
    char *city, *country;
    float population;
} City;

int fileLines(char* fileName) {
  FILE *file = fopen(fileName, "r");
  char currLine[MAX_LINE_LENGTH];
  int numLines = 0;
  while ((fgets(currLine, MAX_LINE_LENGTH, file))) numLines++;
  return numLines-FIRST_LINE;
}

City *readCSV(char* fileName){
  FILE *file = fopen(fileName, "r");
  int numCities = fileLines(fileName);
  City *cityList = malloc(numCities*sizeof(City));
  char currLine[MAX_LINE_LENGTH];

  fgets(currLine, MAX_LINE_LENGTH, file);


  char *buffer;
  int lineCount = 0; // counts the number of lines
  fgets(currLine, MAX_LINE_LENGTH, file); // skip first line
  while ((fgets(currLine, MAX_LINE_LENGTH, file))){
    buffer = strtok(strdup(currLine), ",");
    cityList[lineCount].city = strdup(buffer);
    int column = 1;
    while (buffer != NULL){
      buffer = strtok(NULL, ",");
      switch (column){
        case 4:
            cityList[lineCount].population = atof(strdup(buffer));
            column+= 1;
            break;
        case 5:
            cityList[lineCount].country = strdup(buffer);
            column += 1;
            break;
        default:
            column += 1;
            break;
          }
        }
        lineCount++;
      }
      fclose(file);
      return cityList;
}
int compare(const void *p, const void *q)
{
    float l = ((City *)p)->population;
    float r = ((City *)q)->population;
    return (r - l);
}
void writeCSV(City* cityList, int length, char* fileName){
    FILE *file = fopen(fileName, "w");
    fprintf(file, "city,population,country\n");
    for (int i = 0; i < length; i++) {
        fprintf(file, "%s,%g,%s \n", cityList[i].city, cityList[i].population, cityList[i].country);
    }
    fclose(file);

}
int main() {
    City* cities = readCSV("cities.csv");
    int numCities = fileLines("cities.csv");
    qsort(cities, numCities, sizeof(City), compare);
    writeCSV(cities,numCities,"sorted.csv");


    return 0;
}
