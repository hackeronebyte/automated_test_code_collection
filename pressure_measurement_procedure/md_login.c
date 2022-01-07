md_login()
/**
 * 微商登录
 */
{ 
	char base_str[1024],url[50],u_name[20],pwd[30],tenant_numid[20];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");
    
	strcpy(u_name,lr_eval_string(mendian_loginName()));
	lr_save_string(u_name,"u_name");
	strcpy(pwd,lr_eval_string(mendian_loginPassword()));
	lr_save_string(pwd,"pwd");

	//生产环境固定取值商家ID
	strcpy(tenant_numid,lr_eval_string(mendian_tenant_num_id()));
	lr_save_string(tenant_numid,"tenant_numid");
    
    if (rerun_value()==0) {
	    //测试调式环境随机取值商家ID tenant_num_id
		strcpy(base_str,lr_eval_string("{\"work_nums\":\"{u_name}\","
									   "\"password\":\"{pwd}\",\"channel_num_id\":2,"
									   "\"tenant_num_id\":{merchantid_value}}"));
	}else{
		//运行环境固定取值 tenant_num_id （生产环境）
        strcpy(base_str,lr_eval_string("{\"work_nums\":\"{u_name}\","
									   "\"password\":\"{pwd}\",\"channel_num_id\":2,"
									   "\"tenant_num_id\":{tenant_numid}}"));
	}

	
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
	web_reg_find("Text=\"code\":0","Savecount=login_code_count",LAST);//设置检查点
	/**
	 * {"code":0,"message":"成功","work_nums":"qhw001",
	 * "sid":"33f0429c9ea24139ae0458bd2e165bc8",
	 * "salt":"b1d21afc4b71bf3b9bcc9f6d2895c4ac",
	 * "empe_name":"qhw001","sub_unit_num_id":100001,
	 * "sub_unit_name":"测试微商001"}
	 */
	//微商登sid
    web_reg_save_param("md_sid","RB=\",","LB=\"sid\":\"",LAST);//用关联函数取值
	//微商登录 微商ID
	web_reg_save_param("md_sub_unit_num_id","RB=,","LB=\"sub_unit_num_id\":",LAST);//用关联函数取值
	//获取请求头用于认证
	web_reg_save_param("md_author","RB=\r\n","LB=Authorization: ",LAST);//用关联函数取值
	//https
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("login");
	web_custom_request("login",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=app_key=12000&timestamp={timestamp}&method=ykcloud.user.by.worknums.password.login&sign=&params={base_str}",
		LAST);
	 if(atoi(lr_eval_string("{login_code_count}"))>0){
			lr_end_transaction("login",LR_PASS);
		}else{
            lr_end_transaction("login",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}  
	return 0;
}
