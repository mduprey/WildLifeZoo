#include <iostream>
#include <jni.h>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
    JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
    JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
    JavaVMInitArgs vm_args;                        // Initialization arguments
    JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
    options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
    vm_args.version = JNI_VERSION_1_6;             // minimum Java version
    vm_args.nOptions = 1;                          // number of options
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
    jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
    delete options;    // we then no longer need the initialisation options.
                if (rc != JNI_OK)
                {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
                }
     //=============== Display JVM version =======================================
    cout << "JVM load succeeded: Version ";
    jint ver = env->GetVersion();
    cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

    jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
    if (cls2 == nullptr)
        {
            cerr << "ERROR: class not found !";
    }
    else
        {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else
                        {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
    }


    jvm->DestroyJavaVM();
    cin.get();
}

int i = 0;
vector<string> stringOfFile; //creating a vector for add/remove animals
string track, name, type, subType, egg, nurse, data; //for storing userinput

void AddAnimal()
{
        //Get and edit the track number
        cout << "Track Number: ";
        cin >> track;
        track.insert(track.begin(),7-track.length(),'0');

        //Get and edit animal name
        cout << "Animal Name: ";
        cin >> name;
        name.append(16 - name.length(), ' '); // for character limits

        //Get and edit animal type
        cout << "Animal Type: ";
        cin >> type;
        type.append(16 - type.length(), ' ');// for character limits

        //Get and edit animal sub-type
        cout << "Animal Sub-Type: ";
        cin >> subType;
        subType.append(16 - subType.length(), ' ');// for character limits

        //Get num eggs
        cout << endl << "Number of Eggs: ";
        cin >> egg;

        //get nursing info
        cout << endl << "Nursing (0 for no 1 for yes): ";
        cin >> nurse;
        cout << endl;

        data = track + name + type + subType + egg + nurse;
        stringOfFile.push_back(data);
}


void RemoveAnimal()
{
        //used geeksforgeeks.org for info on std::
        string item = "";
        cout << "Enter Track Number: ";
        cin >> track;

        std::vector<string>::iterator it; //Iterator used to store the position of searched element
        it = std::find(stringOfFile.begin(), stringOfFile.end(), item);//std::find function call
        if(it != stringOfFile.end())
        {
                stringOfFile.erase(it);
        }
        else
        {
                cout <<"Track Number not found or you entered incorrectly..." << endl;
                RemoveAnimal();
        }

}

void LoadDataFromFile()
{
        string file = "zoodata.txt"; //is able to access the txt document
        std::ifstream in(file.c_str());
        if(!in)
        {
                std::cerr << "Cannot open the file... " << file << std::endl; //std output stream for errors
        }
        std::string str;
        while(getline(in,str))
        {
                if(str.size() > 0)
                {
                        stringOfFile.push_back(str);
                }
        }
        cout << "Load complete."<<endl;
        in.close();

}

void SaveDataToFile()
{
        fstream file;
        string file_name = "zoodata.txt"; //is able to access the txt document
        file.open(file_name);
        if(file.fail())
        {
                cout << "File failed to open... ";
        }
        else
        {
                int i = 0;
                int as = stringOfFile.size();
                while(as <= i)
                {
                        file << stringOfFile[as];
                        as--;
                }
        }

}
//creating a function to display the data
void DisplayData()
{
	for(int i=0; i<stringOfFile.size(); i++){
			cout << stringOfFile.at(i) << endl;
		}
}

void DisplayMenu()
{
        int option = 0;
        menu:
        cout << "---------------Menu--------------";
        cout << "\n 1.Load Animal Data\n 2.Generate Date\n 3.Display Animal Data\n 4.Add Record\n 5.Delete Record\n 6.Save Animal Data" << endl<< endl;
        cout << "---------------------------------" << endl;
        cin>> option;

        switch(option)
        {
        case 1:
                //Load Animal Data
                LoadDataFromFile();
                goto menu;
        case 2:
                //Generate Data
                GenerateData();
                goto menu;
        case 3:
                //Display Animal Data (using tabular format/ in rows and columns)
                DisplayData();
                goto menu;
        case 4:
                //Add Record using AddAnimal()
                AddAnimal();
                goto menu;
        case 5:
                //Delete Record using RemoveAniaml()
                RemoveAnimal();
                goto menu;
        case 6:
                //Save Animal Data using the SaveDataToFile()
                SaveDataToFile();
                goto menu;
        case 7:
                cout<<"Quitting"; //Will stop program
                return;
        default:
                //If invalid input is selected
                cout << "\nInvalid Option!";
                cout <<"\nPress any key to continue...";
                goto menu;
        }
}



int main()
{
        DisplayMenu();
        //GenerateData();
        return 1;
}
