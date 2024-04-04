#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
/**
 * \brief Функція заповнення телефонної книги з CSV-файлу (Fill the phone book from a CSV file)
 * \param fileName - назва файлу, з якого будуть
 * \param phoneBook 
 */
void FillPhoneBook(const std::string& fileName, std::unordered_map<std::string, std::string>& phoneBook);
/**
 * \brief Функція пошуку контакту у телефоній книзі за номером телефону (Search for a contact in your phonebook by phone number)
 * \param phoneBook 
 * \param phoneNumber 
 * \return Ім'я контакту
 */
std::string FindContactName(const std::unordered_map<std::string, std::string>& phoneBook, const std::string& phoneNumber);

int main()
{
	std::unordered_map<std::string, std::string> phoneBook;
	std::string CSVFileName;
	std::cout << "Enter CSV file name (.csv included):\n";
	std::cin >> CSVFileName;
	FillPhoneBook(CSVFileName,phoneBook);
	std::string desiredPhoneNumber;
	std::cout << "Enter the phone number to search:\n";
	std::cin >> desiredPhoneNumber;
	std::cout << '\n';
	std::string contactName = FindContactName(phoneBook, desiredPhoneNumber);
	std::cout << "Contact Name: " << contactName << '\n';
	return 0;
}

void FillPhoneBook(const std::string& fileName, std::unordered_map<std::string, std::string>& phoneBook)
{
	std::ifstream file(fileName);
	if(!file.is_open())
	{
		std::cerr << "Error opening file: " << fileName << std::endl;
		return;
	}
	std::string line;
	while(std::getline(file, line))
	{
		size_t commaPosition = line.find(",");
		if(commaPosition != std::string::npos)
		{
			std::string contactName = line.substr(0, commaPosition);
			std::string phoneNumber = line.substr(commaPosition + 1);
			phoneBook[phoneNumber] = contactName;
		}
	}
	file.close();
}
std::string FindContactName(const std::unordered_map<std::string, std::string>& phoneBook, const std::string& phoneNumber)
{
	const auto iterator = phoneBook.find(phoneNumber);
	if(iterator != phoneBook.end())
	{
		return iterator->second;
	}
		return "Contact not found. Try another one.";
}
/**
 * Чому було обрано std::unordered_map?
 * -------------------------------------------------------------------------------------------------------------------------------
 * Часова складність операції пошуку: O(1), за умови хорошої хеш-функції та рівномірного розподілу ключів.
 * Час пошуку імені абонента за номером телефону є постійним і не залежить від розміру телефонної книги.
 * Це робить unordered_map найбільш підходящим вибором для даної задачі, оскільки він пропонує швидкий пошук на основі ключів
 * без значного погіршення продуктивності при збільшенні розміру телефонної книги.
 * Складність простору: O(n), де n - кількість елементів (пар "номер телефону - ім'я"), що зберігаються на карті.
 * Додаткових витрат із подальшим збільшенням складності простору непередбачено.
 * -------------------------------------------------------------------------------------------------------------------------------
 * Що стосовно інших контейнерів?
 * std::vector:
 * Часова складність пошуку: O(n)
 * Просторова складність: O(n) + додаткові накладні витрати для зберігання вказівників на вузли.
 *
 * std::list:
 * Часова складність пошуку: O(n)
 * Просторова складність: O(n) + додаткові накладні витрати для динамічної зміни розміру масиву для векторів.
 *
 * std::map:
 * Часова складність пошуку: O(log(n))
 * Просторова складність: O(n)
 *
 * Пояснення:
 * Для зберігання пар "номер телефону - ім'я" в інших контейнерах, таких як вектори або зв'язані списки, складність простору залишається O(n), де n - кількість елементів, що зберігаються.
 * Однак, ці контейнери можуть вимагати додаткових накладних витрат для зберігання елементів
 * (наприклад, динамічна зміна розміру масиву для векторів, вказівники на вузли для зв'язаних списків),
 * що потенційно може збільшити загальне використання пам'яті у порівнянні з unordered_map.
 * Крім того, операція пошуку у цих контейнерах зазвичай має лінійну часову складність O(n), тобто час, необхідний для пошуку, лінійно зростає зі збільшенням кількості елементів.
 * Це робить їх менш придатними для цієї задачі порівняно з unordered_map, де бажані операції пошуку з постійним часом.
 * Також, було розглянутий контейнер std::map. Є декілька причин, чому його не було обрано:
 *  1) std::unordered_map забезпечує середньостатистичну складність пошуку за постійним часом (O(1)), тоді як std::map забезпечує складність за логарифмічним часом (O(log n)).
 *	2) Хоча обидва контейнери мають однакову просторову складність (O(n)), std::unordered_map, як правило, має кращу середню часову складність для пошукових операцій завдяки індексації на основі хешів.
 *	3) std::map зберігає елементи у відсортованому порядку на основі ключів, що є непотрібним для цієї задачі.
 * 
 */