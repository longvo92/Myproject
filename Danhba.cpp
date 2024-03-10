//             CHUONG TRINH QUAN LY DANH BA DIEN THOAI
// .															Long Vo
// --------------------------------------------------------------------
// .	         Cac chuc nang :
// .		   		1/ Nhap thong tin lien lac bao gom ho ten va sdt.
// .				2/ Quan ly danh sach cac lien lac.
// .				3/ Tim kiem dah sach cac lien lac.
// .				4/ Xoa lien lac.
// .				5/ Cap nhat sdt lien lac.
// .				6/ Nhap, xuat du lieu tu file txt.
// --------------------------------------------------------------------
// .			Update 18/2:
// .				- Hoan thanh khung chuong trinh.
// .				- Hoan thanh cac chuc nang.
// .			Update 19/2:
// .				- Fix loi khi danh ba dang trong (debug error1)
// .				- Chuan hoa ky tu (define function "ChuanHoakytu")
// .			Update 20/2:
// .				- Sap xep lien lac theo ho ten (using algorithm libary soft method, define function "Sapxep")
// .				- Them lua chon cap nhat nhieu so dien thoai 1 luc dua theo ky tu nhap vao
// .				- Tim kiem, xoa va cap nhat lien lac thong minh
// .			Update 21/2:
// .				- Nhap, xuat du lieu tu file txt (using fstream and sstream libary to control data)
// .			Update 22/2:
// .				- Toi uu code, giam do phuc tap (Using set,pair)
// .			Update 23/2:
// .				- Xu ly ky tu nhap xuat, cai thien giao dien nguoi dung.
// .				- Debug loi khien vong lap for vao danhba.end()
// .				- using const value.
// .			Update 1/3:
// .				- Using class.
// .				- Split apllication and logic.
// .				- Xu ly loi dau vao
// .			Last modified:01/03/2024
// .			
// .			To do list:
// .				- control input.
// .				- security control when import file and type data
// .				- return button.
// -------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

const int Them_lien_lac =1;
const int Hienthidanhsach =2;
const int Tim_kiem =3;
const int Xoa_lien_lac =4;
const int Cap_nhat =5;
const int Xuat_file = 6;
const int Mo_file = 7;
const int Thoat =8;

class Xulykytu{
	public:
		void ghepchu(string &a){
				for (int i = a.length(); i >=0;i--){
					if (isspace(a[i])) a.erase(a.begin()+i);
				}
			}
		void tachchu(string &str){
			char kytu= ' ';
			for (int i = str.length(); i >=0;i--){
				if (isupper(str[i])&&i!=0) str.insert(i,1,kytu);
			}
		}
		bool kiemtrakytu(string kytu,string a){
			int j =0;
			for (int i =0;i<a.length();i++){
				if (kytu[j]==a[i]){
					j++;
				if (j==kytu.length()) return true;
			}
			else j=0;
		}
			return false;
		}	
		void ChuanHoakytu(string &str){
			while (str[0]==' '){
				str.erase(str.begin()+0);
			}
			while (str[str.length()-1]==' '){
				str.erase(str.begin()+str.length()-1);
			}
			int TuMoi = 1;
			for (int i = 0; i <str.length();i++){
				if (isspace(str[i])&&isspace(str[i+1])){
					str.erase(str.begin()+i);
					i--;
				}
			}
			for(int i = 0; i < str.length();i++){
				if (TuMoi == 1 && isalpha(str[i])){
					str[i] = toupper(str[i]);
					TuMoi = 0;
				}
				else if (isspace(str[i]) || str[i]=='-'){
					TuMoi=1;
				}
				else {
					str[i] = tolower(str[i]);
					TuMoi = 0;
				}
			}
		}
		bool isNumber(const string &s) {
   	 		return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
		}
};	

class Lienlac:public Xulykytu{
	private:
		set<pair<string,string>> Danhba;
	public:
		void themlienlac(){
			string hoten,dienthoai;
			cin.ignore();
			cout << "Nhap ten:" ;
			getline(cin,hoten);
			ChuanHoakytu(hoten);
			cout<< "Nhap SDT:";
			cin >> dienthoai;
			Danhba.insert(make_pair(hoten,dienthoai));		
		}
		bool Hienthi(){
			if (!Danhba.empty()){
					cout << "Danh sach lien he:"<<endl << "Ten  SDT"<<endl;
					for (auto it = Danhba.begin();it!=Danhba.end();it++){
						cout<< it->first << " " << it->second <<endl;
					}
					return true;
				}
			else return false;
		}
		bool Timkiem(){
			if (!Danhba.empty()){
				int kiemtra = 0;
				string kytu;
				cin.ignore();
				cout << "Vui long nhap ten hoac sdt can tim: ";
				getline(cin,kytu);
				ChuanHoakytu(kytu);
				set<pair<string,string> >::iterator it = Danhba.begin();
				for (it;it!=Danhba.end();it++){
					string b = it->first;
					string c= it->second;
					if(kiemtrakytu(kytu,b)==true){
						cout << "Da tim thay lien he: "<<it->first << " " << it->second<< endl;
						kiemtra = 1;
					}
					if(kiemtrakytu(kytu,c)==true){
						cout << "Da tim thay lien he: "<<it->first << " " << it->second<< endl;
						kiemtra = 1;
					}		
				}
				if (kiemtra == 0){
					cout << "Ten hoac so dien thoai khong ton tai"<<endl;
				}
			}
		}
		bool Xoa(){
			if (!Danhba.empty()){
				int kiemtra = 0;
				string kytu;
				cin.ignore();
				cout << "Vui long nhap ten can xoa: ";
				getline(cin,kytu);
				ChuanHoakytu(kytu);
				set<pair<string,string> >::iterator it = Danhba.begin();
				for (it;it!=Danhba.end();it++){
				string b = it->first;
					if(kiemtrakytu(kytu,b)==true){
						cout<< "Da xoa lien he: "<<it->first<<endl;
						Danhba.erase(it);
						kiemtra = 1;
						break;
					}		
				}	
				if (kiemtra == 0){
					cout << "Ten hoac so dien thoai khong ton tai" <<endl;
				}
			}
		}
		bool Capnhat(){
			if (!Danhba.empty()){
				cout << "Nhap ten nguoi can chinh sua:";
				cin.ignore();
				string kytu;
				int kiemtra=0;
				getline(cin,kytu);
				ChuanHoakytu(kytu);
				set<pair<string,string> >::iterator it = Danhba.begin();	
				for (it;it!=Danhba.end();it++){
					string b = it->first;
					if(kiemtrakytu(kytu,b)==true){
						int bienkiemtra;
						cout << "Co phai ban dang muon sua so cua "<< it->first << " co SDT " << it->second<< " khong" <<endl;
						cout << "1/ Co" <<endl <<"2/ Khong"<<endl;
						cin >> bienkiemtra;
						if (bienkiemtra == 1){
							cin.ignore();
							string b;
							cout << "Nhap SDT moi: ";
							getline(cin,b);
							Danhba.insert(make_pair(it->first,b));	
							Danhba.erase(it);	
							kiemtra++;					
							break;
						}
						else {
							kiemtra++;
						}
							
					}
							
				}
				if (kiemtra==0){
					cout << "Khong co ten nay trong danh sach" << endl;
				}
				else {
					cout << "Da cap nhat!" << endl;}
				}
		}
		bool Xuatfile(){
			string txt;
			cin.ignore();
			cout << "Nhap ten file: ";
			getline(cin,txt);
			ofstream out(txt.c_str());			
			set<pair<string,string> >::iterator it = Danhba.begin();
			for (it; it!=Danhba.end(); it++){
				string a = it->first;
				ghepchu(a);
				if (out.is_open()){
					out << a <<" "<< it->second << " ";
				}
				else {
					cout << "Khong the mo file txt" <<endl;
				}
			}
			out.close();
			cout << "Luu du lieu thanh cong" <<endl; 
		}
		bool Mofile(){
			string txt;
			string str;
			string word;
			vector<string> words;
			cin.ignore();
			cout << "Nhap ten file: ";
			getline(cin,txt);
			ifstream in(txt.c_str());
			if (in){
				getline(in,str);
				in.close();
			}
			else {
				cout << "Kiem tra lai ten file" <<endl;
				return false;
			}
			istringstream iss(str);
			while (iss >> word){
				words.push_back(word);
			}	
			if (!word.empty()){
				for (int i=0; i< words.size();i+=2){
					string hoten;
					string dienthoai;
					hoten = words[i];
					dienthoai = words[i+1];
					tachchu(hoten);
					Danhba.insert(make_pair(hoten,dienthoai));	
				}
			}
			else{
			 	cout << "Khong thanh cong, file trong!" <<endl;
				return false; 
			}
				
		}
		void insert(string hoten, string dienthoai){
			Danhba.insert(make_pair(hoten,dienthoai));	
		}
};


class Giaodien:protected Lienlac{
	private:
		int n;
	public:
		void protectn() {
        	string input;
        	cin >> input;
        	if (!Xulykytu::isNumber(input) || stoi(input) < 1 || stoi(input) > 256) {
            	cerr << "Loi: Gia tri vao khong hop le." << endl;
            	cin.clear();
            	cin.ignore();
        	}
			else {
            	n = stoi(input);
        	}
    	}
		void setup(){
			string str, word;
			vector<string> words;
			string txt1 = "danhba.txt";
			ifstream in(txt1.c_str());
			if (in){
				getline(in,str);
				in.close();
			}
			else {
				cout << "Du lieu dau vao chua duoc nhap!" <<endl;
			}
			istringstream iss(str);
			while (iss >> word){
				words.push_back(word);
			}	
			if (!word.empty()){
				for (int i=0; i< words.size();i+=2){
					string hoten;
					string dienthoai;
					hoten = words[i];
					dienthoai = words[i+1];
					tachchu(hoten);
					insert(hoten,dienthoai);
				}
			}
			cout << "Chao mung den voi ung dung quan ly danh ba!" <<endl;
			cout << "Cac chuc nang bao gom:"<<endl;
			cout << "1/ Them lien lac"<<endl<<"2/ Hien thi danh sach" <<endl<<"3/ Tim kiem"<< endl << "4/ Xoa lien lac"<< endl<< "5/ Cap nhat thong tin" <<endl;
			cout << "6/ Xuat du lieu ra file" <<endl << "7/ Mo du lieu tu file"<<endl <<"8/ Thoat chuong trinh"<<endl;
			cout << "Vui long chon mot chuc nang de bat dau: ";
			protectn();
		}
		void getif(){
			cout << "Chon chuc nang tiep theo :"; 
			protectn();	
		}
		void error1(){
			cerr << "Danh ba hien dang trong vui long them lien he:" << endl;
			Lienlac::themlienlac();
			getif();
		}
		void loop(){
			while (true){
				if (n==Them_lien_lac){
					Lienlac::themlienlac();
					getif();
				}
				else if (n==Hienthidanhsach){
					if (Lienlac::Hienthi()) getif();
					else error1();
				}
				else if (n==Tim_kiem){
					if (Lienlac::Timkiem()) getif();
					else error1();
				}	
				else if (n==Xoa_lien_lac){
					if (Lienlac::Xoa()) getif();
					else error1();
				}	
				
				else if (n==Cap_nhat){
					if (Lienlac::Capnhat()) getif();	
					else error1();
				}
				else if (n==Xuat_file){	
					if (Lienlac::Xuatfile()) getif();
				}
				else if (n==Mo_file){
					if(Lienlac::Mofile()) {
						cout << "Nhap du lieu thanh cong!"<<endl;
						Lienlac::Hienthi();
						getif();					
					}
					else getif();
				}		
				else if (n==Thoat){
					cout << "Cam on ban da su dung ung dung danh ba dien thoai" <<endl <<"Ket thuc chuong trinh";
					break;
				}
				else {
					cout << "Vui long nhap dung yeu cau: "<<endl;
					protectn();
				};
			}
		}
};

int main(){
	Giaodien a;
	a.setup();
	a.loop();
	
	return 0;
}
