#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

class TextEditor {
public:
    TextEditor() {
        undoStack.push("");
        redoStack.push("");
    }

    void run() {
        char choice;
        do {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();  // Clear the newline character from the buffer

            switch (choice) {
                case '1':
                    createDocument();
                    break;
                case '2':
                    displayDocument();
                    break;
                case '3':
                    search();
                    break;
                case '4':
                    saveDocument();
                    break;
                case '5':
                    deleteDocument();
                    break;
                case '6':
                    undo();
                    break;
                case '7':
                    redo();
                    break;
                case '8':
                    std::cout << "Total words written: " << countWords() << std::endl;
                    break;
                case '9':
                    std::cout << "Exiting the text editor. Goodbye!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != '9');
    }

private:
    std::string document;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;

    void displayMenu() {
        std::cout << "\nText Editor Menu:\n";
        std::cout << "1. Create a new document\n";
        std::cout << "2. Display document\n";
        std::cout << "3. Search\n";
        std::cout << "4. Save document\n";
        std::cout << "5. Delete document\n";
        std::cout << "6. Undo\n";
        std::cout << "7. Redo\n";
        std::cout << "8. Count words\n";
        std::cout << "9. Exit\n";
    }

    void createDocument() {
        std::cout << "Enter the content of the document:\n";
        std::getline(std::cin, document);

        undoStack.push(document);
        redoStack = std::stack<std::string>();  // Clear redo stack after creating a new document

        std::cout << "Document created successfully.\n";
    }

    void displayDocument() {
        std::cout << "Document content:\n";
        std::cout << document << "\n";
    }

    void search() {
        std::string query;
        std::cout << "Enter the search query: ";
        std::getline(std::cin, query);

        size_t found = document.find(query);
        if (found != std::string::npos) {
            std::cout << "Found at position " << found << "\n";
        } else {
            std::cout << "Not found.\n";
        }
    }

    void saveDocument() {
        std::ofstream outFile("document.txt");
        if (outFile.is_open()) {
            outFile << document;
            outFile.close();
            std::cout << "Document saved successfully.\n";
        } else {
            std::cout << "Unable to save document.\n";
        }
    }

    void deleteDocument() {
        document.clear();
        undoStack.push(document);
        redoStack = std::stack<std::string>();  // Clear redo stack after deleting the document

        std::cout << "Document deleted successfully.\n";
    }

    void undo() {
        if (undoStack.size() > 1) {
            redoStack.push(undoStack.top());
            undoStack.pop();
            document = undoStack.top();
            std::cout << "Undo successful.\n";
        } else {
            std::cout << "Nothing to undo.\n";
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(redoStack.top());
            redoStack.pop();
            document = undoStack.top();
            std::cout << "Redo successful.\n";
        } else {
            std::cout << "Nothing to redo.\n";
        }
    }

    size_t countWords() const {
        size_t count = 0;
        bool inWord = false;

        for (char c : document) {
            if (std::isalnum(c)) {
                if (!inWord) {
                    inWord = true;
                    ++count;
                }
            } else {
                inWord = false;
            }
        }

        return count;
    }
};

int main() {
    TextEditor textEditor;
    textEditor.run();

    return 0;
}
