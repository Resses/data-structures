#include "binary_tree.h"
#include <iostream>
#include <string>

int main(){
    try{
        
    binary_tree tree;
    char answer = 'y'; //Y or N
    std::string animal;
    std::string question;

    tree = tree.read("animal_game.txt"); //read tree from file
    
    while (answer == 'Y' || answer == 'y')
    {
        std::cerr << "Think of an animal... press Enter (<-') when you are ready" << std::endl;
        while (answer != '\n')
            std::cin.get(answer);
       
        if (tree.isEmpty()){
            tree.addRoot("dog");
        }
        
        binary_tree::node* myNode = tree.getRoot();
        if(!myNode) throw "Error. There is no root node";
        
     
        while (myNode->left) //we're not at a leaf because there's a left child (and that means there's a right child too)
        {
            if(!myNode->right) throw "Error. There is only one child";
            std::cerr << myNode->data << " (Y/N)?"<<std::endl;
            std::cin >> answer;
            while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n'){
                std::cerr << "Invalid response. Please enter y or n" << std::endl;
                std::cin >> answer;
            }
            if(answer == 'Y' || answer == 'y')
                myNode = myNode->right;
            if(answer == 'N' || answer == 'n')
                myNode = myNode->left;
        
        }
        
        //We're at a leaf now.
        std::cerr << "Is it a " << myNode->data << " (Y/N)?" << std::endl;
        std::cin >> answer;
        while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n'){
            std::cerr << "Invalid response. Please enter y or n" << std::endl;
            std::cin >> answer;
        }
        if(answer == 'Y' || answer == 'y')
        {
            std::cerr << "YAY I WIN!" << std::endl;
        }
        if(answer == 'N' || answer == 'n')
        {
            std::cerr << "what animal is it?" << std::endl;
            std::cin >> animal;
            std::cerr << "What Yes/No question could I have asked to identify your animal? " << std::endl;
            std::cin.ignore();
            std::getline(std::cin, question);
            
            std::string temp = myNode->data;
            myNode->data = question;
            tree.addLeft(myNode, temp); //no on left
            tree.addRight(myNode, animal); //yes on right
        }
        
        std::cerr << "Do you want to play again (Y/N)?" << std::endl;
        std::cin >> answer;
        while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n'){
            std::cerr << "Invalid response. Please enter y or n" << std::endl;
            std::cin >> answer;
        }
        std::cin.ignore();
        
    }
    tree.print();
    tree.write("animal_game.txt");
    }
    
    catch(const char* e){
        std::cerr << e << std::endl;
    }
    return 0;
}
