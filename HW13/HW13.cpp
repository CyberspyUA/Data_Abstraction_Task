#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
/**
 * \brief ������� ���������� ��������� ����� � CSV-����� (Fill the phone book from a CSV file)
 * \param fileName - ����� �����, � ����� ������
 * \param phoneBook 
 */
void FillPhoneBook(const std::string& fileName, std::unordered_map<std::string, std::string>& phoneBook);
/**
 * \brief ������� ������ �������� � �������� ���� �� ������� �������� (Search for a contact in your phonebook by phone number)
 * \param phoneBook 
 * \param phoneNumber 
 * \return ��'� ��������
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
 * ���� ���� ������ std::unordered_map?
 * -------------------------------------------------------------------------------------------------------------------------------
 * ������ ��������� �������� ������: O(1), �� ����� ������ ���-������� �� ���������� �������� ������.
 * ��� ������ ���� �������� �� ������� �������� � �������� � �� �������� �� ������ ��������� �����.
 * �� ������ unordered_map ������� ��������� ������� ��� ���� ������, ������� �� ������� ������� ����� �� ����� ������
 * ��� �������� ��������� ������������� ��� �������� ������ ��������� �����.
 * ��������� ��������: O(n), �� n - ������� �������� (��� "����� �������� - ��'�"), �� ����������� �� ����.
 * ���������� ������ �� ��������� ���������� ��������� �������� �������������.
 * -------------------------------------------------------------------------------------------------------------------------------
 * �� �������� ����� ����������?
 * std::vector:
 * ������ ��������� ������: O(n)
 * ���������� ���������: O(n) + �������� ������� ������� ��� ��������� ��������� �� �����.
 *
 * std::list:
 * ������ ��������� ������: O(n)
 * ���������� ���������: O(n) + �������� ������� ������� ��� �������� ���� ������ ������ ��� �������.
 *
 * std::map:
 * ������ ��������� ������: O(log(n))
 * ���������� ���������: O(n)
 *
 * ���������:
 * ��� ��������� ��� "����� �������� - ��'�" � ����� �����������, ����� �� ������� ��� ��'���� ������, ��������� �������� ���������� O(n), �� n - ������� ��������, �� �����������.
 * �����, �� ���������� ������ �������� ���������� ��������� ������ ��� ��������� ��������
 * (���������, �������� ���� ������ ������ ��� �������, ��������� �� ����� ��� ��'������ ������),
 * �� ���������� ���� �������� �������� ������������ ���'�� � �������� � unordered_map.
 * ��� ����, �������� ������ � ��� ����������� �������� �� ����� ������ ��������� O(n), ����� ���, ���������� ��� ������, ����� ������ � ���������� ������� ��������.
 * �� ������ �� ���� ���������� ��� ���� ������ �������� � unordered_map, �� ����� �������� ������ � �������� �����.
 * �����, ���� ����������� ��������� std::map. � ������� ������, ���� ���� �� ���� ������:
 *  1) std::unordered_map ��������� ������������������� ��������� ������ �� �������� ����� (O(1)), ��� �� std::map ��������� ��������� �� ������������ ����� (O(log n)).
 *	2) ���� ������ ���������� ����� �������� ���������� ��������� (O(n)), std::unordered_map, �� �������, �� ����� ������� ������ ��������� ��� ��������� �������� ������� ���������� �� ����� �����.
 *	3) std::map ������ �������� � ������������� ������� �� ����� ������, �� � ���������� ��� ���� ������.
 * 
 */