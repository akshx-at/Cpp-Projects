/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
using namespace std; 

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    // read in the data using the function
    // split the string into     words and and return that as vectors
    // trim the words
    // once we have it as one big vector we will iterate through the 2D vector and store the words in the boxes of the array 
    // read the string from the csv file
    // now as the whole thing is a big string, first break the string depending on the newline characters
    // then we split each sting in a vector depending on commas and store them as vectors
    // so we will have one big vector which will divide the string depending on the lines
    // Within the big vector we will small vectors for each line, dividing the line depending on the comma

    V2D student;
    std::string outputstring;
    outputstring = file_to_string(filename);
    std::vector<std::string> wordvector;
    int vectnum = split_string( outputstring, '\n',  wordvector);
    //so now wordvect stores the a vector for each line
    //now we iterate through the main vector and split the value in each vector as strings
    for (int i  = 0; i < vectnum; i++){
        std::string val = wordvector[i];
        std::vector<std::string> tempvector;
        int vectnum1 = split_string(val, ',',  tempvector);
        for (int j = 0; j < vectnum1; j++) {
            std::string& field = tempvector[j];
            tempvector[j] = trim(field);
        }
        student.push_back(tempvector);
    }
    return student;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    V2D correct_data;
    correct_data.resize(cv.size());

    for(size_t i = 0; i < cv.size(); i++){
            for(size_t j = 0; j< cv[i].size(); j++){
                correct_data[i].push_back(cv[i][j]);
            } //birthday man we collectiveky fuced up coz last time he celebrated one day late so i thoght it was tomorow as per my insta story so idk what to do rn coz if i wish him rn its like oh fuck my bad i forgot happy bday but if i wait till night i can act like its a surpise either ways we are getting him a cake and stuff
    }

    std::map<std::string,std::vector<std::string>> studentmap;
    std::map<std::string,std::vector<std::string>> classmap;

    //populating the maps
    for (size_t i = 0; i < student.size(); i++) {
        std::string key = student[i][0];
        std::vector<std::string> values;
        for (size_t j = 1; j < student[i].size(); j++) {
            values.push_back(student[i][j]);
        }
        studentmap[key] = values;
    }
    // to keep track of the key order because the order is getting fucked 
    std::vector<std::string> orderkeeper;
    for (size_t i = 0; i < cv.size(); i++) {
        std::string key1 = cv[i][0];
        orderkeeper.push_back(key1);
        std::cout<<key1<<std::endl;
        std::vector<std::string> values1;
        for (size_t j = 1; j < cv[i].size(); j++) {
            values1.push_back(cv[i][j]);
        }
        //std::cout<<key1<<std::endl;
        classmap[key1] = values1;
    }
    // to check if the student has the course and the course has the student as well
     for(size_t it = 0; it < correct_data.size(); it++){
        for(size_t i = 1; i < correct_data[it].size(); i++){
            std::string stu = correct_data[it][i];
            std::string clas = correct_data[it][0];
            std::vector<std::string> val = studentmap[stu]; // what do you wanna do rn? wisah him? maybe get a cake or something fo rhhim rn? cake we are getting at night, we should treat him to dinner mane. man we have to wish him rn but hwo do we do it smoothly??
            // lets take him out for lunch or paris super crepes or something rn.. okay, rn rn or what do you think? idk man we could say we are going for the concert and then take him out rn okay yea so rn????yeah
            int flag = 0;
                for(size_t j = 0; j < val.size(); j++){
                    if(clas == val[j]){
                        flag = 1;
                }
            }
            if(flag == 0){
                correct_data[it].erase(correct_data[it].begin()+i);
            }
        }
     }
    // to check if the student is invalid, if it is then get rid of the student
    for(size_t it = 0 ; it < correct_data.size(); it++){
        for(size_t i = 1; i < correct_data[it].size(); i++){
            if(studentmap.find(correct_data[it][i]) == studentmap.end()){
                correct_data[it].erase(correct_data[it].begin()+i);
            }
        }
    }

    // to check if the course is empty and if it is, remove it
    for(size_t it = 0 ; it < correct_data.size(); it++ ){
        if(correct_data[it].size() == 0 || correct_data[it].size() == 1){
            correct_data.erase(correct_data.begin() + it);
    }

    // add key-value pairs from classmap to correct_data
// for(const auto& p : classmap) {
//     for (size_t i = 0; i < orderkeeper.size(); i++ ){
//         if(orderkeeper[i] == p.first){
//             //std::cout<<"why is this ucker not working"<< std::endl;
//             // std::cout<<orderkeeper[i]<<std::endl;
//             const std::string& key = p.first;
//     // std::cout<<p.first<<std::endl;
//             const std::vector<std::string>& values = p.second;
//             std::vector<std::string> row = {key};
//             row.insert(row.end(), values.begin(), values.end());
//             correct_data.push_back(row);
//         }
//     }
// }
}
    return correct_data;
}


/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */


// std::vector<std::vector<bool>> matrix_constructor(const V2D &courses){
//     std::vector<std::vector<bool>> adj_matrix(courses.size(), std::vector<bool>(courses.size(), false));
//     for (size_t i = 0; i < courses.size(); i++ ){
//         for(size_t j = 1; j < courses.at(i).size(); j++ ){
//             // we are at a specific studnet
//             // if that student is in another class set the bool to true
//             std::string tempstu = courses.at(i).at(j);
//             for (size_t k = 0; k < courses.size(); k++ ){
//                 for(size_t l = 1; l < courses.at(k).size(); l++ ){
//                     //std::cout<<adj_matrix.at(i).at(j);
//                     if(i != k && tempstu == courses.at(k).at(l)){
//                         adj_matrix.at(i).at(k) = true;
//                         adj_matrix.at(k).at(i) = true;
//                         //std::cout<<"bruh"<< std::endl;
//                     }
//                 }
//               //      std::cout<<adj_matrix.at(i).at(k);
//             }
//                //                     std::cout<<std::endl;
//         }
//            //                                 std::cout<<std::endl;
//     }
//     return adj_matrix;
// }

// Constructs an adjacency matrix from the given course schedule, and colors each course so that no adjacent courses have the same color
V2D colorCourses(const V2D& courses, const std::vector<std::string>& timeslots, int startindex) {
    // Construct the adjacency matrix
    std::vector<std::vector<bool>> adj_matrix(courses.size(), std::vector<bool>(courses.size(), false));
    for (size_t i = 0; i < courses.size(); ++i) {
        for (size_t j = 1; j < courses[i].size(); ++j) {
            const std::string& tempstu = courses[i][j];
            for (size_t k = i + 1; k < courses.size(); ++k) {
                for (size_t l = 1; l < courses[k].size(); ++l) {
                    if (tempstu == courses[k][l]) {
                        adj_matrix[i][k] = true;
                        adj_matrix[k][i] = true;
                        break;
                    }
                }
            }
        }
    }

    // Color the courses
    std::vector< int> colors(courses.size(), -1);
    int idx = startindex;
    for (size_t k = 0; k < courses.size(); k++) {
        std::vector<bool> neighborColors(timeslots.size(), false);
        for (size_t j = 0; j < courses.size(); j++) {
            if (adj_matrix[idx][j] && colors[j] != -1) {
                neighborColors[colors[j]] = true;
            }
        }
        for (size_t x = 0; x < neighborColors.size(); x++) {
            if (!neighborColors[x]) {
                colors[idx] = x;
                break;
            }
        }
        if (colors[idx] == -1) {
            V2D err{{"-1"}};
            return err;
        }
        idx = (idx + 1) % courses.size();
    }

    // Return the colored schedule
    V2D coloredSchedule;
    for (size_t i = 0; i < timeslots.size(); i++) {
        std::vector<std::string> coursesInSlot;
        coursesInSlot.push_back(timeslots[i]);
        for (size_t j = 0; j < courses.size(); j++) {
            if (colors[j] == int(i)) {
                coursesInSlot.push_back(courses[j][0]);
            }
        }
        coloredSchedule.push_back(coursesInSlot);
    }
    return coloredSchedule;
}




V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    // An adjacency matrix to store the edges between the classes and students so that we can reuse them later
    // We will reuse them to assign colors to the vertices

for (size_t i = 0; i < courses.size(); ++i) {
    V2D returned = colorCourses(courses, timeslots, i);
    if (returned[0][0] != "-1") {
        return returned;
    }
}

V2D errors = {{"-1"}};
return errors;

}