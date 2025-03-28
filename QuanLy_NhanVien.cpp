
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

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
    void setID(const string& newID) { employeeID = newID; }
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

        file.close();
    }

    void WriteToFile() {
        string filename = "Employees.csv";
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto& emp : ds_nhanvien) {
            file << emp.getID() << ","
                << emp.getName() << ","
                << emp.getPosition() << ","
                << fixed << setprecision(0) << emp.getSalary() << ","
                << emp.getWorkingHours() << "\n";
        }

        file.close();
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

    void InputEmployeeData(string &employeeID,string &name, string &position, double &salary,int &workingHours)
    {
        int maNhanVienSo;
        string chucVuNhap;
        // Nhập mã nhân viên
        while (true) {
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            cin >> maNhanVienSo;
            if (cin.fail())  // Trả về giá trị true nếu lần nhập trước thất bại
            {
                cin.clear(); // Xoá cờ lỗi
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu lỗi
                cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if ((maNhanVienSo) >= 1 && (maNhanVienSo) <= 999) {
                    if (CheckDuplicateID(maNhanVienSo))
                    {
                        cout << "Ma nhan vien da ton tai. Vui long nhap lai." << endl;
                    }
                    else
                        break;
                }
                else {
                    cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
                }
            }
        }

        // Nhập họ tên
        cout << "Nhap ho ten (toi da 35 ky tu): ";
        cin.ignore();
        getline(cin, name);
        while (name.length() > 35) {
            cout << "Ho ten qua dai. Vui long nhap lai: ";
            getline(cin, name);
        }

        // Nhập chức vụ
        while (true) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            cin >> chucVuNhap;
            if (chucVuNhap == "NV" || chucVuNhap == "QL") {
                break;
            }
            else {
                cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập lương
        while (true) {
            cout << "Nhap luong (toi da 20,000,000 va khong am): ";
            cin >> salary;
            if (salary >= 0 && salary <= 20000000) {
                break;
            }
            else {
                cout << "Luong khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Nhập số giờ làm
        while (true) {
            cout << "Nhap so gio lam (toi da 12): ";
            cin >> workingHours;
            if (workingHours >= 0 && workingHours <= 12) {
                break;
            }
            else {
                cout << "So gio lam khong hop le. Vui long nhap lai." << endl;
            }
        }

        // Định dạng mã nhân viên
        stringstream ss;
        ss << setw(3) << setfill('0') << maNhanVienSo;
        string maNhanVienFormatted = ss.str();

        // Thêm tiền tố vào mã nhân viên dựa trên chức vụ
        if (chucVuNhap == "NV") {
            employeeID = "NV" + maNhanVienFormatted;
            position = "Nhan vien";
        }
        else {
            employeeID = "QL" + maNhanVienFormatted;
            position = "Quan ly";
        }
    }

    void AddEmployee() {
        string employeeID;
        string name;
        string position;
        double salary;
        int workingHours;

        InputEmployeeData(employeeID, name, position, salary, workingHours);
        
        ds_nhanvien.emplace_back(employeeID, name, position, salary, workingHours);
        WriteToFile();
    }

    bool CheckDuplicateID(const int ID)
    {
        for (const auto& emp : ds_nhanvien)
        {
            string ID_temp = emp.getID();
            if (stoi(ID_temp.substr(2)) == ID)
                return true;
        }
        return false;
    }

    int SreachIndexEmployeeByID(const string ID)
    {
        for (int i = 0; i < ds_nhanvien.size(); i++)
        {
            if (ds_nhanvien[i].getID() == ID)
                return i;
        }
        return -1;
    }

    void EditEmployee() {
        string ID_sreach;
        cout << "Nhap ma nhan vien can sua: ";
        cin >> ID_sreach;
        cin.ignore();
    
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
        string ID, name, pos, chucVuNhap;
        int maNhanVienSo=0, workingHours;
        double salary;

        // Nhập ID mới
        string maNhanVienSo_ToStr; // Nhập bắng str để kiểm tra xem có bỏ trống không
        while (true) {
            bool check = false;
            cout << "Nhap ma nhan vien (toi da 3 so): ";
            getline(cin, maNhanVienSo_ToStr);
            if (!maNhanVienSo_ToStr.empty()) // Kiểm tra nếu không nhâp thì bỏ qua
            {
				for (char c : maNhanVienSo_ToStr) // Kieemr tra xem có phải số không
				{
					if (isalpha(c))
					{
						cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
						check = true;
                        break;
					}
				}
                if (!check)
                {
                    maNhanVienSo = stoi(maNhanVienSo_ToStr);
                    if ((maNhanVienSo) >= 1 && (maNhanVienSo) <= 999) {
                        if (CheckDuplicateID(maNhanVienSo))
                        {
                            cout << "Ma nhan vien da ton tai. Vui long nhap lai." << endl;
                        }
                        else
                            break;
                    }
                    else
                    {
                        cout << "Ma nhan vien khong hop le. Vui long nhap lai." << endl;
                    }
                }
            }
            else break;
        }

        // Nhập tên mới
        while (true)
        {
            cout << "Nhap ho ten (toi da 35 ky tu): ";
            getline(cin, name);
            if (!name.empty())
            {
                if (name.length() > 35) {
                    cout << "Ho ten qua dai. Vui long nhap lai.";
                }
                else
                {
                    ds_nhanvien[viTri].setName(name);
                    break;
                }
            }
            else break;
        }

        // Nhập chức vụ mới
        while (true) {
            cout << "Nhap chuc vu (NV hoac QL): ";
            getline(cin, chucVuNhap);
            if (!chucVuNhap.empty())
            {
                if (chucVuNhap == "NV" || chucVuNhap == "QL") {
                    //Định dạng lại chức
                    if (chucVuNhap == "NV")
                        ds_nhanvien[viTri].setPosition("Nhan vien");
                    else
                        ds_nhanvien[viTri].setPosition("Quan ly");
                    break;
                }
                else {
                    cout << "Chuc vu khong hop le. Vui long nhap lai." << endl;
                }
            }
            else break;
        }

        // Nhập số lương mới
        string salary_ToStr;
        while (true) {
            cout << "Nhap luong (toi da 20,000,000 va khong am): ";
            getline(cin, salary_ToStr);
            if (!salary_ToStr.empty())
            {
                salary = stoi(salary_ToStr);
                if (salary >= 0 && salary <= 20000000) {
                    ds_nhanvien[viTri].setSalary(salary);
                    break;
                }
                else {
                    cout << "Luong khong hop le. Vui long nhap lai." << endl;
                }
			}
			else break;
        }

        // Nhập giờ làm mới
        string workingHours_ToStr;
        while (true)
        {
            cout << "Nhap so gio lam (toi da 12): ";
            getline(cin, workingHours_ToStr);
            if (!workingHours_ToStr.empty())
            {
                workingHours = stoi(workingHours_ToStr);
                if (workingHours >= 0 && workingHours <= 12) {
                    ds_nhanvien[viTri].setWorkingHours(workingHours);
                    break;
                }
                else {
                    cout << "So gio lam khong hop le. Vui long nhap lai." << endl;
                }
			}
			else break;

        }

		// Định dạng mã nhân viên
        if (!maNhanVienSo_ToStr.empty())
        {
            stringstream ss;
            string pos_temp = ds_nhanvien[viTri].getPosition();
            ss << setw(3) << setfill('0') << maNhanVienSo;
            string maNhanVienFormatted = ss.str();
            if (pos_temp == "Nhân viên")
            {
				ID = "NL" + maNhanVienFormatted;
            }
            else
            {
                ID = "QL" + maNhanVienFormatted;
            }
			ds_nhanvien[viTri].setID(ID);
        }

        cout << "Sua thong tin nhan vien thanh cong!" << endl;
        WriteToFile();
    }

	void SreachEmployeeByID()
	{
		string ID_sreach;
		cout << "Nhap ma nhan vien can tim: ";
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
		cout << "Nhap ma nhan vien can xoa: ";
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

// Example usage
int main() {
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

        if (cin.fail())
        {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    return 0;

}
