
// utils/menu.cppm
export module crs.utils.menu ;


import <iostream>;
import <vector>;
import <functional>;

export namespace crs.utils {

class Menu{
private :
using OptionHandler=std ::function<void ()>;


struct Option{
std :: string text ;
OptionHandler handler ;
};

std :: vector<Option> options ;
std :: string title ;

public :
Menu(const char *title_="Menu") :title(title_){}

void addOption(const char *text ,OptionHandler handler ){
options .push_back({text ,handler });
}

void show ()const{
std :: cout <<"==== "<<title <<" ===="<<" \n";
for(size_t i=0 ;i<options .size();i ++){
std :: cout <<"("<<i+1<<") "<<options [i].text<<"\n";
}
std :: cout <<"(0) Exit"<<"\n";
}

int getChoice ()const{
int choice ;
std :: cout <<"Please select an option: ";
std :: cin >>choice ;
return choice ;
}

void run (){

while(true){
show();
int choice =getChoice();
if(choice ==0){
break ;
}
if(choice >0 &&choice <=(int)options .size()){
options [choice -1].handler();
}else{
std :: cout <<"Invalid option! Please try again."<<"\n";
}
}
}

};

}
