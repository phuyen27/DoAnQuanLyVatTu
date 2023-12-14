#include "Bill.cpp"

#define MAX_EMPLOYEE 500

typedef struct employee {
    string nameEmployee, employeeID, gender;
    BILL_NODE billList = NULL;
}EMPLOYEE;

struct employeeList {
    int numberEmployee = 0;
    EMPLOYEE *employeeNode[MAX_EMPLOYEE];
};

bool emptyCheck(employeeList employeeList) {
    if (employeeList.numberEmployee == 0) return true;
    return false;
}

bool fullCheck(employeeList employeeList) {
    if(employeeList.numberEmployee == MAX_EMPLOYEE) return true;
    return false;
}

int searchEmployee(employeeList employeeList, string employeeId) {
    for(int i = 0; i < employeeList.numberEmployee; i++) {
        if(strcmp(employeeList.employeeNode[i]->employeeID.c_str(), employeeId.c_str()) == 0) return i;
    }
    return -1;
}

int findPosition(employeeList employeeList, string employeeName) {
    for(int i = 0; i < employeeList.numberEmployee; i++) {
        if(strcmp(employeeList.employeeNode[i]->nameEmployee.c_str(), employeeName.c_str()) >= 0) return i;
    }
    return employeeList.numberEmployee;
}

bool addEmployeeToPosition(employeeList &employeeList, EMPLOYEE employee, int index) {
    if(index < 0 || index > employeeList.numberEmployee || fullCheck(employeeList)) return false;
    employeeList.employeeNode[employeeList.numberEmployee] = new EMPLOYEE;
    for(int i = employeeList.numberEmployee; i > index; i--) {
        *employeeList.employeeNode[i] = *employeeList.employeeNode[i-1];
    }
    *employeeList.employeeNode[index] = employee;
    employeeList.numberEmployee++;
    return true;
}

void bubbleSort(employeeList &employeeList) {
    for (int i = 0; i < employeeList.numberEmployee - 1; i++) {
        for (int j = 0; j < employeeList.numberEmployee - i - 1; j++) {
            if (strcmp(employeeList.employeeNode[j]->nameEmployee.c_str(),
                       employeeList.employeeNode[j + 1]->nameEmployee.c_str()) > 0) {
                // Hoán đổi nhân viên
                EMPLOYEE *temp = employeeList.employeeNode[j];
                employeeList.employeeNode[j] = employeeList.employeeNode[j + 1];
                employeeList.employeeNode[j + 1] = temp;
            }
        }
    }
}


bool sortListByName(employeeList &employeeList, EMPLOYEE employee) {
   int index = findPosition(employeeList, employee.nameEmployee);
   bool result = addEmployeeToPosition(employeeList,employee,index);
   bubbleSort(employeeList);
   return result;
}

void inputEmployee(EMPLOYEE &employee) {
    cin.ignore();
    cout << "Nhap ten nhan vien: ";
    getline(cin, employee.nameEmployee);
    cout << "Nhap ma nhan vien: ";
    getline(cin, employee.employeeID);
    cout << "Nhap gioi tinh: ";
    getline(cin, employee.gender);
}

void addEmployeeList(employeeList &employeeList) {
    char choose;
    do {
        EMPLOYEE  employee;
        inputEmployee(employee);
        bool result = sortListByName(employeeList,employee);
        if(!result) cout << "\nKhong the them nhan vien, danh sach da day hoac co loi!";
        else cout << "\nNhan vien da duoc them vao danh sach!";

        cout << "\nBan co muon nhap tiep nhan vien? (y/n): ";
        cin >>choose;
    } while (choose == 'Y' || choose == 'y');
}


void employeeTitle() {
    cout << setw(17) << left << "\nHo ten nhan vien" << "\t";
    cout << setw(17) << left << "Ma so nhan vien" << "\t";
    cout << setw(17) << left << "Gioi tinh" << "\t\n";
}


void outputEmployee(EMPLOYEE *employee) {
    cout << setw(17) << left << employee->nameEmployee << "\t";
    cout << setw(17) << left << employee->employeeID << "\t";
    cout << setw(17) << left << employee->gender << "\t\n";
}

void outputBillEmployee(employeeList employeeList) {
      cout << setw(20) << left << "Ma so hoa don" <<"\t";
      cout << setw(20) << left << "Loai" << "\t";
      cout << setw(20) << left << "Tong chi phi" << "\t\n";
      for(int i = 0; i < employeeList.numberEmployee; i++) {
      outputAllBill(employeeList.employeeNode[i]->billList);
    }
}

void outputListEmployee(employeeList employeeList) {
    cout << "\n============================================================";
    cout << "\n\t\t\tDANH SACH NHAN VIEN";
    employeeTitle();
        cout << "============================================================\n";
    for(int i = 0; i < employeeList.numberEmployee; i++) {
       outputEmployee(employeeList.employeeNode[i]);
       cout << "-------------------------------------------------------------\n";
    }
}

