gys_login()
/**
 * 代理商登录
 */
{

	char base_str1[1024],url[50];
	strcpy(url,lr_eval_string(gys_base_url("/system/login")));
    lr_save_string(url,"url");


	web_reg_find("Text=\"code\":0","Savecount=gys_login_code_count",LAST);//设置检查点
	//"sid": "9a4fc847266c44028b426c14d60d926b",
	web_reg_save_param("gys_sid","RB=\",","LB=\"sid\":\"",LAST);//用关联函数取值 
	// user_num_id "key":"5315"}, 确认订单需要的参数
	web_reg_save_param("user_num_id","RB=\"},","LB=\"key\":\"",LAST);//用关联函数取值 

	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("gys_login");
	
	web_custom_request("gys_login",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/json",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/json",
		"Body={\"x\":\"{dayhour}25\",\"username\":\"s{supply_unit_num_id}\",\"password\":\"Gys12345601\",\"tenantNumId\":\"{gysmerchantid_value}\"}",
		LAST);
	if(atoi(lr_eval_string("{gys_login_code_count}"))>0){
			lr_end_transaction("gys_login",LR_PASS);
		}else{
			lr_end_transaction("gys_login",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
	return 0;
}
