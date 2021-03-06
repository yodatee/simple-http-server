#include "file.h"

string file::get_filename(string request) {
    string filename;
    char delim = ' ';

    request.erase(0, request.find(delim) + 1);
    filename = request.substr(0, request.find(delim));

    //remove first char
    filename.erase(0, 1);

    return filename;
}

string file::get_fileending(string filename) {
    char delim = '.';
    filename.erase(0, filename.find(delim) + 1);
    return filename;
}

bool file::file_exists(string filename) {
    ifstream file_f(filename);
    return (bool) file_f;
}

string file::open_file(string filename) {

    if(filename == ""){
        filename = "index.html";
    }

    if (file_exists(FILE_PATH + filename)) {
        string temporary_data;
        string data;
        ifstream infile;
        infile.open(FILE_PATH + filename);

        getline(infile, temporary_data);
        data = temporary_data;
        while (infile) {
            getline(infile, temporary_data);
            data = data + temporary_data;
        }
        infile.close();
        return data;
    } else {
        return "file not found";
    }

}