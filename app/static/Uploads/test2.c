int Add(int x, int y){
	return x + y;
}

int main(){
	int x[10];
	int y, z;
	int i;
	
	y = 2;
	i = 0;
	x[i] = i;
	do{		
		if(x[i] == y){
			z = Add(x[i], y);
		}else{
			z = y - x[i];
		}
		x[++i] = i;
	}while(x[i] <= y);
	
	fun(y, z);
	
	return 0;
}

void fun(y, z){
	int a[3] = {-1, 2, 3};
	int 1b = y + z;
	int c@ = y / z;
	
	a[0] = y + z
	a[1] = y - z;
	a[2 += z;
}