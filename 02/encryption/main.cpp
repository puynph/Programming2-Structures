#include <iostream>
#include <string>
#include <cctype>

std::string const LENGTH_ERROR = "Error! The encryption key must contain 26 characters.",
                  LOWERCASE_ERROR = "Error! The encryption key must contain only lower case characters.",
                  CONTENT_ERROR = "Error! The encryption key must contain all alphabets a-z.",
                  PLAINTEXT_LOWERCASE_ERROR = "Error! The text to be encrypted must contain only lower case characters.";


bool validate_key_length(std::string const &key)
{
    // does key contain only 26 letters ?
    return key.length() == 26;
}

bool validate_key_only_lowercase(std::string const &key)
{
    for(char c : key)
    {
        if(std::isupper(c))
        {
            return false;
        }
    }
    return true;
}

bool validate_contents(std::string const &key)
{
    for(char letter = 'a'; letter <= 'z'; letter++)
    {
        if(key.find(letter) == std::string::npos)
        {
            return false;
        }
    }
    return true;
}

std::string encrypt(std::string const &key, std::string const &plaintext)
{
    std::string encrypted_text = "";
    for(char letter : plaintext)
    {
        int index = letter - 'a';
        encrypted_text += key.at(index);
    }
    return encrypted_text;
}

int main()
{
    std::cout << "Enter the encryption key: ";

    std::string key;
    std::getline(std::cin, key);
    if (!validate_key_length(key))
    {
        std::cout << LENGTH_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    if (!validate_key_only_lowercase(key))
    {
        std::cout << LOWERCASE_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    if (!validate_contents(key))
    {
        std::cout << CONTENT_ERROR << std::endl;
        return EXIT_FAILURE;
    }


    //user input

    std::string plaintext;
    std::cout << "Enter the text to be encrypted: ";
    std::getline(std::cin, plaintext);

    if (!validate_key_only_lowercase(plaintext))
    {
        std::cout << PLAINTEXT_LOWERCASE_ERROR << std::endl;
        return EXIT_FAILURE;
    }

    std::string encrypted_text = encrypt(key, plaintext);

    std::cout << "Encrypted text: " << encrypted_text << std::endl;

    return 0;

}

