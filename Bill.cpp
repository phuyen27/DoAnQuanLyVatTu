#include "Material.cpp"

typedef struct billDetail{
    string materialID;
    int numberMaterial,unit;
    float VAT;
}BILL_DETAIL;

struct BillDetailNode {
    BILL_DETAIL billdetail;
    BillDetailNode*next;
};
typedef BillDetailNode* BILL_DETAIL_NODE;

typedef struct bill {
    string billID, createdDate, billType;
    // billType: input or output
    BILL_DETAIL_NODE  listBillDetail;
}BILL;

struct BillNode {
    BILL *bill;
    BillNode*next;
};
typedef BillNode*BILL_NODE;

BILL_DETAIL_NODE createBillDetailNode(BILL_DETAIL billDetail) {
    BILL_DETAIL_NODE newNode = new BillDetailNode();
    newNode->billdetail.materialID = billDetail.materialID;
    newNode->billdetail.numberMaterial = billDetail.numberMaterial;
    newNode->billdetail.unit = billDetail.unit;
    newNode->billdetail.VAT = billDetail.VAT;
    newNode->next = NULL;
    return newNode;
}


BILL_NODE createBillNode(BILL bill) {
    BILL_NODE newNode = new BillNode();
    newNode->bill = new BILL;
    newNode->bill->billID = bill.billID;
    newNode->bill->createdDate = bill.createdDate;
    newNode->bill->billType = bill.billType;
    newNode->bill->listBillDetail = NULL;
    newNode->next = NULL;
    return newNode;
}


void inputBillDetail(BILL_DETAIL& billDetail, MATERIAL_NODE_TREE root) {
       bool findID;
       do {
            cout << "Nhap ma vat tu: ";
            getline(cin, billDetail.materialID);
            findID = findMaterial(root, billDetail.materialID);
            if (findID == false) {
                cout << "Ma vat tu khong ton tai, vui long nhap lai!" << endl;
            }
       }while (findID == false);   
        cout << "Nhap so luong vat tu: ";
        cin >> billDetail.numberMaterial;
        cout << "Nhap don gia vat tu: ";
        cin >> billDetail.unit;
        cout << "Nhap VAT: ";
        cin >> billDetail.VAT;        
        
}

void inputBill(BILL &bill) {
    cout << "\nNhap ma so hoa don: ";
    getline(cin,bill.billID);
    cout << "Nhap ngay lap: ";
    getline(cin, bill.createdDate);
    cout << "Nhap loai hoa don (I/O): ";
    getline(cin, bill.billType);
}

void addBillDetail(BILL_NODE &bill,BILL_DETAIL_NODE billDetail) {
    if(bill->bill->listBillDetail == NULL) {
        bill->bill->listBillDetail = billDetail;
    }
    else {
        BILL_DETAIL_NODE temp = bill->bill->listBillDetail;
        while(temp->next != NULL) temp = temp->next;
        temp->next = billDetail;
    }
}

void inputAllBill(BILL_NODE& head, MATERIAL_NODE_TREE material) {
    char choose;
    char chooseDetail;
    do {
        BILL_NODE newBill = new BillNode;
        BILL bill;
        inputBill(bill);
        newBill = createBillNode(bill);
        if (head == NULL) head = newBill;
        else {
            BILL_NODE temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBill;
        }
        
        do {
            BILL_DETAIL_NODE newBillDetail = new BillDetailNode;
            BILL_DETAIL billDetail;
            inputBillDetail(billDetail, material);
           
            MATERIAL_NODE_TREE foundMaterial = findMaterialByID(material, billDetail.materialID);
            if (bill.billType== "I") {     
                foundMaterial->material.numberInStock = billDetail.numberMaterial +  material->material.numberInStock;
            } else if (bill.billType == "O") {
                foundMaterial->material.numberInStock = material->material.numberInStock - billDetail.numberMaterial;   
            }

            if(foundMaterial->material.numberInStock < 0) cout << "\nSo luong ton kho khong du de xuat kho!";
            else material->material.numberInStock = foundMaterial->material.numberInStock;

            newBillDetail = createBillDetailNode(billDetail);
            addBillDetail(newBill,newBillDetail);

            cout<< "\nNhap tiep chi tiet hoa don?(y/n): ";
            cin >> chooseDetail;
            cin.ignore();
           
        }while (chooseDetail == 'y');

      
        cout << "Nhap tiep hoa don cua nhan vien? (y/n): ";
        cin >> choose;
        cin.ignore();
    } while (choose == 'y');
}

void billDetailTitle() {
    cout << setw(10) << left << "Ma vat tu" << "\t";
    cout << setw(10) << left << "So luong" <<"\t";
    cout << setw(10) << left << "Don gia" << "\t";
    cout << setw(10) << left << "VAT (%)" << "\t\n";
}

void billTitle() {
    cout << "\n\t---Hoa don---\n";
    cout << setw(20) << left << "Ma so hoa don" <<"\t";
    cout << setw(20) << left << "Ngay lap" << "\t";
    cout << setw(20) << left << "Loai" << "\t\n";
}

void outputBillDetail(BILL_DETAIL_NODE BillDetail) {
   
    cout << setw(10) << left<< BillDetail->billdetail.materialID << "\t";
    cout << setw(10) << left << BillDetail->billdetail.numberMaterial << "\t";
    cout << setw(10) << left << BillDetail->billdetail.unit << "\t";
    cout << setw(10) << left << BillDetail->billdetail.VAT << "\t\n";
  
}

void outputBill(BILL_NODE bill) {
        billTitle();
        cout << setw(20) << left << bill->bill->billID << "\t";
        cout << setw(20) << left << bill->bill->createdDate << "\t";
        cout << setw(20) << left << bill->bill->billType << "\t\n";
        BILL_DETAIL_NODE temp = bill->bill->listBillDetail;
        cout << "\n\t---Chi tiet hoa don---\n";
        billDetailTitle();
        while(temp != NULL) {
            outputBillDetail(temp);
            temp = temp->next;
        }
}


void outputAllBill(BILL_NODE bill) {
    BILL_NODE temp = bill;
    while(temp != NULL) {
        outputBill(temp);
        temp = temp->next;
    }
}

long long invoiceCosts(BILL_DETAIL_NODE billDetail) {
    float materialCost = 0;
    BILL_DETAIL_NODE temp = billDetail;
    while(temp != NULL) {
        materialCost += (temp->billdetail.numberMaterial*temp->billdetail.unit* double((100 + temp->billdetail.VAT)/ 100.0));
        temp = temp->next;
    }
    return materialCost;
}

void outputInvoiceCost(BILL_NODE bill) {
    BILL_NODE temp =bill;
    while(temp != NULL) {
        cout << setw(20) << left << temp->bill->billID <<"\t";
        cout << setw(20) << left << temp->bill->billType << "\t";
        long long toltalCost = invoiceCosts(temp->bill->listBillDetail);
        cout << setw(20) << left << toltalCost << "\t\n";
        temp= temp->next;
    }
}