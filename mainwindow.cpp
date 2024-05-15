#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPushButton>
#include <QWidget>
#include <fstream> // Include for ifstream
#include <QString>
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include "trieclass.h"
#include <QMessageBox>
using namespace std;
bool corrected=false;
std::string filename;
ifstream userInput;
std::string stdText;
bool checked =false;
vector <std::pair<vector<string>,string>> results;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
// che,sameh  ,sameh   cherif,

    void transfer(istringstream &stream,vector<string> storage)
{
    string temp="",ideal;
    int pos=-999;
    while(stream >>temp)
    {
        pos=-999;
        ideal="";
        for(int i=0;i<temp.length();i++)
        {
            if(int(temp[i]) <65 || int(temp[i]) > 122  || ( int(temp[i]>=91) && int(temp[i])<=96 ))
            {
                pos=i;
            }
        }
        if(pos==0)
        {
            for(int i=1;i<temp.length();i++)
            {
                ideal+=temp[i];
            }
            storage.push_back(ideal);
        }
        else if(pos>temp.length()/2)
        {
            for(int i=0;i<temp.length()-1;i++)
            {
                ideal+=temp[i];
            }
            storage.push_back(ideal);
        }
        else if(pos==-999)
        {
            ideal=temp;
            storage.push_back(ideal);
        }
        else
        {
            string second="";
            for(int i=0;i<pos;i++)
            {
                ideal+=temp[i];
            }
            for(int i=pos+1;i<temp.length();i++)
            {
                second+=temp[i];
            }
            storage.push_back(ideal);
            storage.push_back(second);
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit_2->setPlainText("");
    corrected=false;
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open File", "", "All Files (*)");

    filename = fileName.toStdString();
    userInput.open(filename);
    string fulltext="",temp;
    ifstream x(filename);
    while(getline(x,temp))
    {
        fulltext+=temp;
    }
    ui->textEdit->setText(QString::fromStdString(fulltext));
}
// you use c samh cherif
void highlightWordsInTextEdit(const std::vector<std::string>& words, QTextEdit* textEdit)
{
    QTextDocument *document = textEdit->document();

    for (const std::string& word : words) {
        QString qWord = QString::fromStdString(word);
        QTextCursor cursor(document);

        while (!cursor.isNull() && !cursor.atEnd()) {
            cursor = document->find(qWord, cursor);

            if (!cursor.isNull()) {
                QTextCharFormat highlightFormat;
                highlightFormat.setBackground(Qt::yellow);
                cursor.mergeCharFormat(highlightFormat);

                // Remove the highlighting from the added text
                cursor.clearSelection();
            }
        }
    }
}

#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QRegularExpression>

#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QRegularExpression>

#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QRegularExpression>

void removeHighlightFromTextEdit(QTextEdit* textEdit) {
    QTextDocument* document = textEdit->document();
    QTextCursor cursor(document);

    // Create a regular expression to match any text
    QRegularExpression regex(".*");

    // Iterate through the entire document
    for (QTextBlock block = document->begin(); block.isValid(); block = block.next()) {
        QTextCursor blockCursor = QTextCursor(block);
        blockCursor.movePosition(QTextCursor::EndOfBlock);

        while (blockCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor)) {
            QString text = blockCursor.selectedText();
            if (text.trimmed().isEmpty()) {
                continue; // Skip empty spaces
            }

            QTextCharFormat format = blockCursor.charFormat();
            format.setBackground(Qt::transparent);
            blockCursor.setCharFormat(format);
        }
    }

    // Move the cursor back to the start of the document
    cursor.movePosition(QTextCursor::Start);
    textEdit->setTextCursor(cursor);
}



std::string replaceNonAlphabetic(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (isalpha(c)) {
            result += c;
        } else {
            result += ' ';
        }
    }
    return result;
}
int countWords(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    int wordCount = 0;

    while (iss >> word) {
        wordCount++;
    }

    return wordCount;
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_2->setPlainText("");


    if(ui->textEdit->toPlainText()!="")
    {
        checked=true;
        string temp;
        removeHighlightFromTextEdit(ui->textEdit);
        //QColor white(255, 255, 255);
        //ui->textEdit->setTextColor(white);
        vector<string> words_only;


        Trie dictionary;
        string word;
        QString qText = ui->textEdit->toPlainText(); // Get the text as QString
        stdText = qText.toStdString(); // Convert QString to std::string

        std::istringstream ss(replaceNonAlphabetic(stdText));
        cout<<stdText;

        cout << "Loading data from wordlist.txt" << endl;
        ifstream wordlist("wordlist.txt");
        if (!wordlist.is_open()) {
            cout << "Error opening wordlist.txt file. Please ensure the file wordlist.txt is in the project's path." << endl;

        }

        while (wordlist >> word) {
            dictionary.insert(word);
        }

        /*dictionary.insert("Hello");
        dictionary.insert("world");
        dictionary.insert("programming");
        dictionary.insert("languages");*/


        cout << "Total words in dictionary: " << dictionary.getCount() << endl;



        while(ss>>word)
        {

            if (dictionary.search(word))
            {

                cout << word << " is spelled correctly." << std::endl;
            }
            else
            {
                cout << word << " is misspelled." << std::endl;
                vector<string> suggestions = dictionary.suggestCorrections(word);

                //getSuggestions(word);
                words_only.push_back(word);
                pair<vector<string>, string> temp_pair;
                temp_pair.second = word;
                cout << "Suggestions for '" << word << "':" << endl;
                sort(suggestions.begin(), suggestions.end());
                string lastword = "";
                for (const string& suggestion : suggestions) {
                    cout << suggestion << endl;
                    temp_pair.first.push_back(suggestion);
                }
                results.push_back(temp_pair);
            }



        }
        cout << endl;
        cout << "results vector: ";
        for (int i = 0; i < results.size(); i++)
        {
            cout << "word is mis: " << results[i].second << endl;
            cout << "suggestions: " << endl;
            for (int j = 0; j < results[i].first.size(); j++)
            {
                cout << results[i].first[j]<<endl;
            }

        }

        highlightWordsInTextEdit(words_only,ui->textEdit);
        cout<<endl;
        for(int i=0;i<words_only.size();i++)
        {
            cout<<words_only[i]<<endl;
        }


        ui->textEdit_2->setText("");

        if(results.size()==0)
        {
            ui->textEdit_2->setText("No mistaked detected !");
        }
        else
        {
            for(int i=0;i<results.size();i++)
            {
                ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + '\n' + "this word is misspelled : " + QString::fromStdString(results[i].second) + '\n' + "suggestions:");

                for(int j=0;j<results[i].first.size();j++)
                {
                    ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + '\n'+QString::fromStdString(results[i].first[j]));
                }
                ui->textEdit_2->setText(ui->textEdit_2->toPlainText() + '\n');
            }
        }
        double per= (words_only.size()*100)/countWords(replaceNonAlphabetic(stdText));
        QMessageBox::warning(this, ("Report"), "Percentage of Misspelled Words: " + QString::number(per) +"%", QMessageBox::Ok);


    }
    else
    {
        QMessageBox::warning(this, ("Error"), "Please upload a file or enter text first! ", QMessageBox::Ok);
    }
}

void replaceWord(string& input, string& word, const std::string& replacement) {



    // Check if the word exists in the input string
    size_t pos = input.find(word);
    if (pos != std::string::npos) {
        // Replace the word with the replacement word
        input.replace(pos, word.length(), replacement);
    }


}

void MainWindow::on_pushButton_3_clicked()
{
#include <string>
#include <vector>
#include <algorithm>
    ofstream x("results.txt");
    if(checked)
    {


        if(!corrected)
        {


            for(int i=0;i<results.size();i++)
            {
                if(results[i].first.size()>0)
                {
                    replaceWord(stdText,results[i].second,results[i].first[0]);
                }

                cout<<results[i].first.size()<<endl;
            }
            ofstream x("results.txt");
            x<<stdText;
            QMessageBox::warning(this, ("Succesful Download"), "File Downloaded Succesfully!", QMessageBox::Close);
        }
        else{
            x<<ui->textEdit->toPlainText().toStdString();
            QMessageBox::warning(this, ("Succesful Download"), "File Downloaded Succesfully!", QMessageBox::Close);
        }
    }
    else if(ui->textEdit->toPlainText() == "")
    {
        QMessageBox::warning(this, ("Error"), "Please upload a file or enter text first! ", QMessageBox::Ok);}
    else{
        QMessageBox::warning(this, ("Error"), "Please check for mistakes first! ", QMessageBox::Ok);}

    }


void MainWindow::on_pushButton_4_clicked()
{

    if(checked==true)
    {
        for(int i=0;i<results.size();i++)
        {
            if(results[i].first.size()>0)
            {
                replaceWord(stdText,results[i].second,results[i].first[0]);
            }

            cout<<results[i].first.size()<<endl;
        }


        corrected=true;
        ui->textEdit->setText(QString::fromStdString(stdText));
    }
    else
    {
        QMessageBox::warning(this, ("Error"), "please check for the mistakes first", QMessageBox::Ok);
    }

}





void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit_2->setPlainText("");
    corrected = checked = false;

}


void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit->setPlainText("");
    corrected = checked = false;

}

