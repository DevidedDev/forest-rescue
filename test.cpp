

#include <iostream>
#include <fstream>
#include <cstring>


struct Score{
    char name[25];
    int score;
    Score();
};

namespace fileSys{
    void saveScore(Score);
    void getScores(Score topScores[5]);
    void createScoreFile();
    static const char *FILE_PATH = "./bin/scores.bin";
}


int main()
{   
    fileSys::createScoreFile();
     Score scores[5];
    Score tmp;
    strcpy(tmp.name, "janez novak");
    tmp.score = 14;
    fileSys::saveScore(tmp);
    fileSys::getScores(scores);
    
    
    for(int i = 0; i <5; i++){
        std::cout << i << ". " <<
        scores[i].name << " " << scores[i].score << std::endl;
    }
   
    

    return 0;
}

void fileSys::createScoreFile(){
    std::ifstream datai;
    datai.open(FILE_PATH, std::ios::binary );
    if(!datai.is_open()){
        std::ofstream datao;
        datao.open(FILE_PATH, std::ios::binary);
        Score tmp;
        for(int i = 0; i < 5; i++){
            datao.write((char*)&tmp, sizeof(tmp));
        }
        std::cout << "Score file created" << std::endl;
        
        datao.close();
    }else{
        std::cout << "Scores file already exists" << std::endl;
    }
    datai.close();
    

}

void fileSys::saveScore(Score p_score){
    std::ofstream datao;
    std::ifstream datai;

    datao.open(FILE_PATH, std::ios::binary | std::ios::ate| std::ios::in ) ;
    datai.open(FILE_PATH, std::ios::binary);
    if(!datai.is_open() ){ //empty file
        std::cout << "Error: can not save score. No scores.bin file to write to" << std::endl;
        return;

        
    }
    Score tmp;
    
        int i;
        bool newHighscore = false;
        
        for(i = 0; i<5; i++){
            datai.read((char*)&tmp, sizeof(tmp));

            if(p_score.score > tmp.score){
                newHighscore = true;
                break;
            }
        }

        if(!newHighscore){
            std::cout << "No new higschore" << std::endl;
            return;
        }

        //write your value
    if(i != 5){ //check if new value is smaller than other values
        datao.clear();
        datao.seekp(sizeof(Score)*i, std::ios::beg);
        std::cout << "Datao location:" << datao.tellp() << std::endl;
        datao.write((char*)&p_score, sizeof(Score));
        Score tmp2;
        for(i; i <5; i++){

            datai.read((char*)&tmp2, sizeof(Score));
            datao.write((char*)&tmp, sizeof(Score));
            tmp = tmp2;
        }

    }
    std::cout << "Score saved!" << std::endl;
    datai.close();
    datao.close();

        
    
}

void fileSys::getScores(Score topScores[5]){
    
    std::ifstream datai;
    datai.open(FILE_PATH, std::ios::binary);
    if(datai.is_open()){
        int i;
        Score tmp;
        for(int i = 0;  i < 5; i++){
            
            datai.read((char*)&tmp, sizeof(tmp));

            topScores[i] = tmp;
        }
        
    }else{
        std::cout << "No scores exist yet." << std::endl;
    }
    datai.close();
    
}
Score::Score()
:name(""), score(0)
{

    
}