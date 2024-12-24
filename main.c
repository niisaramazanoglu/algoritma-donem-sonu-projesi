#include <stdio.h>
#include <string.h>

#define FILE_WORD_LENGTH 50
#define FILE_WORD_SIZE 3000

// Benzerlik oranını hesaplayan fonksiyon
double similar_text(char *word1, char *word2)
{
    long length1 = strlen(word1);
    long length2 = strlen(word2);
    int match_count = 0;
    int min_word_length ;

    if (length1 < length2)
        {
       min_word_length = length1;
        }
    else
        {
        min_word_length = length2;
        }

    for (int i = 0; i < min_word_length; i++)
    {
        if (word1[i] == word2[i])
        {
            match_count++; // Ayni sirada eşleşen harf yakalandığında eşleşme sayacını 1 artır.
        }
    }
   // eşleşen harf sayısını doğru olan kelimenin harf sayısına bölerek fonksiyonu döndür.
    return (double)match_count / length2;
    // bölümün sonucu ondalıklı çıkabilme ihtimalini göze alarak değişken değiştirdik.
}

int main() {

    char word[FILE_WORD_LENGTH];
    //dosyadaki kelimeleri tutan, satır ve her bir kelimenin uzunluğu kadar sütun içeren bir dizi tanımlıyoruz.
    char file_words[FILE_WORD_SIZE][FILE_WORD_LENGTH];
    int word_count = 0; //dosyadan okunan kelime sayısı.
    char best_match[FILE_WORD_SIZE];

    FILE *file;

    // Kullanıcıdan kelime al
    printf("Search:");
    scanf("%s", word);

    // words.txt dosyasını aç
    file = fopen("words.txt", "r");

    // dosya herhangi bir sebepten dolayı açılamadıysa programı bitir.
    if (file==NULL)
    {
        printf("File could not be opened.\n");
        return 0;
    }

    // Dosyadaki kelimeleri dosyanın sonuna gelene kadar oku.
    while (word_count != EOF)
    {
        word_count++;
        if (word_count >= FILE_WORD_SIZE)
        {
            break;
        }
        // Eğer dosya boşsa
        if (word_count == 0)
        {
            printf("The file is empty or no words were found.\n");

        }
        fscanf(file, "%s", file_words[word_count]);
    }
    //words.txt dosyasını kapa.
    fclose(file);

    double max_similarity = 0.0;

    // En iyi eşleşmeyi bul
    for (int i = 0; i < word_count; i++)
    {
        double similarity = similar_text(word, file_words[i]);
        if (similarity > max_similarity)
        {
            max_similarity = similarity;
            //dosyamızdaki en iyi eşleşen i. satırdaki kelimeyi best_match dizisine atıyoruz.
            strcpy(best_match, file_words[i]);
        }
    }

    // Best_match e atanan en iyi eşleşmenin sonucunu ekrana yazdırıyoruz.
    if (max_similarity > 0.0)
    {
        printf("Did you mean? %s (%.2f)", best_match, max_similarity);
    }
    else
    {
        printf("No matching\n");
    }

    return 0;
}


