vuser_init()
{
	return 0;
}

//微商用户名
char *mendian_loginName(){
	char uname[20];
	if(environment()==1){
      strcpy(uname,"qw001");
	}else{
      strcpy(uname,"qw002");
	}
	return uname;

}

//总商用户
char *zongdian_loginName(){
	char uname[20];
	if(environment()==1){
      strcpy(uname,"wq001");
	}else{
      strcpy(uname,"qw123");
	}
	return uname;

}


//总商密码
char *zongdian_loginPassword(){
	char pwd[20];
	if(environment()==1){
      strcpy(pwd,"qw123321");
	}else{
      strcpy(pwd,"qw123222");
	}
	return pwd;

}

//微商密码
char *mendian_loginPassword(){
	char pwd[20];
	if(environment()==1){
      strcpy(pwd,"qw123321");
	}else{
      strcpy(pwd,"qw123222");
	}
	return pwd;

}

//微商登录登录商家ID
char *mendian_tenant_num_id(){
	char tenant_id[20];
	if(environment()==1){
      strcpy(tenant_id,"100110");
	}else{
      strcpy(tenant_id,"100111");
	}
	return tenant_id;
}


//总商登录商家ID
char *zongdian_tenant_num_id(){
	char tenant_id[20];
	if(environment()==1){
      strcpy(tenant_id,"100211");
	}else{
      strcpy(tenant_id,"100412");
	}
	return tenant_id;
}




//微商代理商商品编码
char *mendian_itemid_barcode(){
	char barcode_id[20];
	if(environment()==1){
      strcpy(barcode_id,"100111");
	}else{
      strcpy(barcode_id,"15431");
	}
	return barcode_id;

}

//微商代理商ID
char *mendian_supply_unit_num_id(){
	char supply_unit_num_id[20];
	if(environment()==1){
      strcpy(supply_unit_num_id,"100211");
	}else{
      strcpy(supply_unit_num_id,"41912");
	}
	return supply_unit_num_id;

}




int environment(){
	// 生产环境：1;测试环境：0
	return 0;
	
}

int rerun_value(){
	// 运行环境：1;调式环境：0
	return 0;

}
//微商总商请求URL做统一处理
char *base_url(){
	char url[50];
	if (environment()==1) {
        strcpy(url,"https://www.pro.app.com/gateway");
	}
	else{
		strcpy(url,"http://ww.test.app.com/gateway");
	}

    lr_output_message("******************** url:%s *************************",url);
	return url;
}


//代理商请求URL做统一处理
char *gys_base_url(char* url_suffix){
	char url[50],urls[150];
	if (environment()==1) {
        strcpy(url,"https://www.pro.app.com");
	}
	else{
		strcpy(url,"http://www.test.app.com");
	}

	strcpy(urls, url);
	strcat(urls, url_suffix);
    lr_output_message("******************** url:%s *************************",urls);
	return urls;
}



const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
char *base64_encode(const char* data, int data_len) 
{ 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
      
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            //printf("tmp = %d\n", tmp); 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            //printf("%.2X", changed[i]); 
            f++; 
        } 
    } 
    *f = '\0'; 
      
    return ret; 
}
