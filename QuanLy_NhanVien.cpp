
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

// Forward declarations for Order and Product classes
class Order;
class Product;

class Employee {
private:
    string employeeID;
    string name;
    string position;
    double salary;
    int workingHours;

public:
    // Constructor
    Employee(string id = "", string n = "", string pos = "", double sal = 0.0, int hours = 0)
        : employeeID(id), name(n), position(pos), salary(sal), workingHours(hours) {
    }
    
    //// Các phương thức xử lý công việc
    //void processOrder(Order order) {
    //    // Implementation would depend on Order class
    //}

    //void updateStock(Product product, int quantity) {
    //    // Implementation would depend on Product class
    //}
    
    // Phương thức hiển thị tiêu đề (static)
    static void displayHeader() {
        cout << left
            << setw(8) << "Ma NV"
            << setw(20) << "Ten"
            << setw(15) << "Chuc vu"
            << right
            << setw(12) << "Luong"
            << setw(10) << "Gio lam"
            << endl;

        cout << setfill('-');
        cout << setw(7) << "" << " "
            << setw(19) << "" << " "
            << setw(14) << "" << " "
            << setw(12) << "" << " "
            << setw(10) << "" << endl;
        cout << setfill(' '); // Reset fill character
    }

    // Phương thức hiển thị hàng dữ liệu
    void displayRow() const {
        cout << left
            << setw(8) << employeeID
            << setw(20) << name
            << setw(15) << position
            << right
            << setw(12) << fixed << setprecision(0) << salary
            << setw(10) << workingHours
            << endl;
    }


    // Getters
    string getID() const { return employeeID; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    int getWorkingHours() const { return workingHours; }

    // Setters
    void setID(const string& newID) 
    { 
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << newID;
        string ID_Formatted = ss.str();
		employeeID = ID_Formatted;
    }
    void setName(const string& newName) {name = newName; }
    void setSalary(double newSalary) { salary = newSalary; }
    void setPosition(const string& newPos) { position = newPos; }
    void setWorkingHours(int hours) { workingHours = hours; }

};

class EmployeeManager
{
private:
    vector<Employee> ds_nhanvien;
public:
    void ReadFromFile() {
        string filename = "Employees.csv";
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, pos, salStr, hoursStr;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pos, ',');
            getline(ss, salStr, ',');
            getline(ss, hoursStr);

            try {
                double salary = stod(salStr);
                int hours = stoi(hoursStr);
                ds_nhanvien.emplace_back(id, name, pos, salary, hours);
            }
            catch (const exception& e) {
                cerr << "Error parsing data: " << e.what() << endl;
            }
        }

        SortByID();

        file.close();
    }

    void WriteToFile() {
        string filename = "Employees.csv";
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

		SortByID();

        for (const auto& emp : ds_nhanvien) {
            file << emp.getID() << ","
                << emp.getName() << ","
                << emp.getPosition() << ","
                << fixed << setprecision(0) << emp.getSalary() << ","
                << emp.getWorkingHours() << "\n";
        }

        file.close();
    }

	void SortByID()
	{
        if (ds_nhanvien.size() > 1)
        {
            sort(ds_nhanvien.begin(), ds_nhanvien.end(), [](const Employee& emp1, const Employee& emp2) {
                return stoi(emp1.getID()) < stoi(emp2.getID());
                });
        }
	}

    void displayInfor_ALL()
    {
		cout << "============ Danh sach nhan vien ============" << endl;
        Employee::displayHeader();
        for (const auto& emp : ds_nhanvien)
        {
            emp.displayRow();
        }
    }

    bool checkInputID(string ID)
    {
		if (ID.empty()) // Kiểm tra xem có bỏ trống không
		{
			cout << "Ma nhan vien khong duoc de trong. Vui long nhap lai." << endl;
			return false;
		}
		for (char c : ID) // Kiểm tra xem có phải số không
        {
            if (isalpha(c))
            {
                cout << "Ma nhan vien khong chua ky tu. Vui long nhap lai." << endl;
                return false;
            }
        }
		if (stoi(ID) >= 1 && stoi(ID) <= 999) // Kiểm tra xem có trong khoảng không
        {
			if (checkDuplicateID(stoi(ID))) // Kiểm tra xem có trùng không
            {
                cout << "Ma nhan vien da ton tai. Vui long nhap lai." << endl;
                return false;
            }
            else
                return true;
        }
        else
        {
            cout << "Ma nhan vien chi tu (1 -> 999). Vui long nhap lai." << endl;
            return false;
        }
    }

	bool checkInputName(string name)
	{
		if (name.empty()) // Kiểm tra xem có bỏ trống không
		{
			cout << "Ho ten khong duoc de trong. Vui long nhap lai." << endl;
			return false;
		}
        for (char c : name) // Kiểm tra xem có phải chữ không
        {
            if (isdigit(c))
            {
                cout << "Ten khong chua so. Vui long nhap lai." << endl;
                return false;
            }
        }
		if (name.length() > 35)
		{
			cout << "Ho ten qua dai. Vui long nhap lai." << endl;
			return false;
		}
		return true;
	}

	bool checkInputPosition(string pos)
	{
		if (pos.empty()) // Kiểm tra xem có bỏ trống không
		{
			cout << "Chuc vu khong duoc de trong. Vui long nhap lai." << endl;
			return false;
		}
		if (pos == "NV" || pos == "QL")
			return true;
		else
		{
			cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
			return false;
		}
	}

	bool checkInputSalary(string salary)
	{
		if (salary.empty()) // Kiểm tra xem có bỏ trống không
		{
			cout << "Luong khong duoc de trong. Vui long nhap lai." << endl;
			return false;
		}
        for (char c : salary) // Kiểm tra xem có phải số không
        {
			if (isalpha(c))
			{
				cout << "Luong khong chua ky tu. Vui long nhap lai." << endl;
				return false;
			}
        }
        if (stod(salary) >= 0 && stod(salary) <= 20000000) // Kiểm tra xem có trong khoảng không
        {
                return true;
        }
        else
        {
			cout << "Luong chi tu (0 -> 20,000,000). Vui long nhap lai." << endl;
            return false;
        }
	}

	bool checkInputWorkingHours(string workingHours)
	{
		if (workingHours.empty()) // Kiểm tra xem có bỏ trống không
		{
			cout << "So gio lam khong duoc de trong. Vui long nhap lai." << endl;
			return false;
		}
		for (char c : workingHours) // Kiểm tra xem có phải số không
		{
			if (isalpha(c))
			{
				cout << "So gio lam khong chua ky tu. Vui long nhap lai." << endl;
				return false;
			}
		}
		if (stoi(workingHours) >= 0 && stoi(workingHours) <= 12) // Kiểm tra xem có trong khoảng không
		{
			return true;
		}
		else
		{
			cout << "So gio lam chi tu (0 -> 12). Vui long nhap lai." << endl;
			return false;
		}
	}

    bool checkDuplicateID(const int ID)
    {
        for (const auto& emp : ds_nhanvien)
        {
            if (stoi(emp.getID()) == ID)
                return true;
        }
        return false;
    }

    void AddEmployee() {
        string employeeID;
        string name;
        string position;
        double salary;
        int workingHours;

		// Nhập ID nhân viên
        bool check = false;
        string ID_temp;
        while (!check)
        {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            getline(cin, ID_temp);
            check = checkInputID(ID_temp);
        }
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << ID_temp;
        employeeID = ss.str();

        // Nhập tên nhân viên
        check = false;
		while (!check)
		{
			cout << "Nhap ho ten (toi da 35 ky tu): ";
			getline(cin, name);
			check = checkInputName(name);
		}

		// Nhập chức vụ
        check = false;
        string pos_temp;
        while (!check)
		{
			cout << "Nhap chuc vu (NV hoac QL): ";
			getline(cin, pos_temp);
			check = checkInputPosition(pos_temp);
        }
		// Định dạng lại chức vụ
        if (pos_temp == "NV") {
            position = "Nhan vien";
        }
        else {
            position = "Quan ly";
        }

        // Nhập lương
		check = false;
		string salary_temp;
		while (!check)
		{
			cout << "Nhap luong (toi da 20,000,000 va khong am): ";
			getline(cin, salary_temp);
			check = checkInputSalary(salary_temp);
		}
		salary = stod(salary_temp);

		// Nhập số giờ làm
		check = false;
		string workingHours_temp;
		while (!check)
		{
			cout << "Nhap so gio lam (toi da 12): ";
			getline(cin, workingHours_temp);
			check = checkInputWorkingHours(workingHours_temp);
		}
		workingHours = stoi(workingHours_temp);
        
        ds_nhanvien.emplace_back(employeeID, name, position, salary, workingHours);
        WriteToFile();
    }

    int SreachIndexEmployeeByID(const string ID_so)
    {
        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << ID_so;
        string ID_Formatted = ss.str();
        for (int i = 0; i < ds_nhanvien.size(); i++)
        {
            if (ds_nhanvien[i].getID() == ID_Formatted)
                return i;
        }
        return -1;
    }

    void EditEmployee() {
        string ID_sreach;
        cout << "Nhap ma nhan vien can sua: ";
		getline(cin, ID_sreach);
    
        // Tìm kiếm nhân viên trong danh sách
        int viTri = SreachIndexEmployeeByID(ID_sreach);
        if (viTri == -1) {
            cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
            return;
        }

        // Hiển thị thông tin hiện tại
        cout << "Thong tin nhan vien hien tai:" << endl;
		Employee::displayHeader();
		ds_nhanvien[viTri].displayRow();
		cout << endl;

        // Cho phép sửa thông tin
        cout << "Nhap thong tin moi (nhan Enter de giu nguyen):" << endl;
    
        // Sửa thông tin nhân viên
        string employeeID;
        string name;
        string position;
        double salary;
        int workingHours;

        // Nhập ID mới
        string ID_temp; // Nhập bắng str để kiểm tra xem có bỏ trống không
		bool check = false;
        while (!check) {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            getline(cin, ID_temp);
            if (!ID_temp.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
            {
                check = checkInputID(ID_temp);
                if (check)
                {
                    // Định dạng mã nhân viên
                    stringstream ss;
                    ss << setw(3) << setfill('0') << ID_temp;
                    employeeID = ss.str();
					ds_nhanvien[viTri].setID(employeeID);
                }
			}
			else break;
        }

        // Nhập tên mới
		check = false;
		while (!check) {
			cout << "Nhap ho ten (toi da 35 ky tu): ";
			getline(cin, name);
            if (!name.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
            {
                check = checkInputName(name);
                if (check)
                {
                    ds_nhanvien[viTri].setName(name);
                }
            }
            else break;
		}

        // Nhập chức vụ mới
		check = false;
		string pos_temp;
        while (!check) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            getline(cin, pos_temp);
            if (!pos_temp.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
            {
                check = checkInputPosition(pos_temp);
                if (check)
                {
                    if (pos_temp == "NV") {
                        position = "Nhan vien";
                    }
                    else {
                        position = "Quan ly";
                    }
                    ds_nhanvien[viTri].setPosition(position);
                }
            }
            else break;
        }

        // Nhập số lương mới
		check = false;
		string salary_Temp;
		while (!check) {
			cout << "Nhap luong (toi da 20,000,000 va khong am): ";
			getline(cin, salary_Temp);
			if (!salary_Temp.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
			{
				check = checkInputSalary(salary_Temp);
				if (check)
				{
					salary = stod(salary_Temp);
					ds_nhanvien[viTri].setSalary(salary);
				}
			}
			else break;
		}

        // Nhập giờ làm mới
        string workingHours_temp;
		check = false;
		while (!check) {
			cout << "Nhap so gio lam (toi da 12): ";
			getline(cin, workingHours_temp);
			if (!workingHours_temp.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
			{
				check = checkInputWorkingHours(workingHours_temp);
				if (check)
				{
					workingHours = stoi(workingHours_temp);
					ds_nhanvien[viTri].setWorkingHours(workingHours);
				}
			}
			else break;
		}

        cout << "Sua thong tin nhan vien thanh cong!" << endl;
        WriteToFile();
    }

	void SreachEmployeeByID()
	{
		string ID_sreach;
		cout << "Nhap ma nhan vien can tim (nhap so) : ";
		cin >> ID_sreach;
		cin.ignore();
		// Tìm kiếm nhân viên trong danh sách
		int viTri = SreachIndexEmployeeByID(ID_sreach);
		if (viTri == -1) {
			cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
			return;
		}
		// Hiển thị thông tin hiện tại
		cout << "Thong tin nhan vien can tim la:" << endl;
		Employee::displayHeader();
		ds_nhanvien[viTri].displayRow();
	}

	void RemoveEmployeeByID()
	{
		string ID_sreach;
		cout << "Nhap ma nhan vien can xoa (nhap so): ";
		cin >> ID_sreach;
		cin.ignore();
		// Tìm kiếm nhân viên trong danh sách
		int viTri = SreachIndexEmployeeByID(ID_sreach);
		if (viTri == -1) {
			cout << "Khong tim thay nhan vien co ma " << ID_sreach << endl;
			return;
		}
		else {
			// Xóa nhân viên khỏi cả hai danh sách
			ds_nhanvien.erase(ds_nhanvien.begin() + viTri);
			cout << "Xoa thanh cong nhan vien :" << endl;
            Employee::displayHeader();
			ds_nhanvien[viTri].displayRow();
            cout << endl;
			WriteToFile();
		}
	}
};

static void menu_QL_NhanVien()
{
    EmployeeManager ql;
    int chon = 0;
    ql.ReadFromFile();
    while (chon != 8)
    {
        system("cls");
        cout << "============ Quan ly nhan vien ============\n"
            << "1. Them nhan vien\n"
            << "2. Cap nhat thong tin nhan vien\n"
            << "3. Hien thi danh sach nhan vien\n"
            << "4. Tim nhan vien theo ID\n"
            << "5. Xoa nhan vien theo ID\n"
            << "6. Chua co\n"
            << "7. Chua co\n"
            << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;
        cin.ignore();

        if (cin.fail())  // Trả về giá trị true nếu lần nhập trước thất bại
        {
            cin.clear(); // Xoá cờ lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu lỗi
            cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            cout << "\nAN Enter de quay lai man hinh chon....";
            cin.get();
        }
        else
        {
            switch (chon)
            {
            case 1:
                ql.AddEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 2:
                ql.EditEmployee();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 3:
                ql.displayInfor_ALL();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 4:
                ql.SreachEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 5:
                ql.RemoveEmployeeByID();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 6:
                //ql.TimNhanVienTheoMa();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 7:
                //ql.XoaNhanVien();
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            case 8:
                cout << "Thoat chuong trinh\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                cout << "\nAN Enter de quay lai man hinh chon....";
                cin.get();
                break;
            }
        }
    }
}



int main() {
    menu_QL_NhanVien();

    return 0;

}
