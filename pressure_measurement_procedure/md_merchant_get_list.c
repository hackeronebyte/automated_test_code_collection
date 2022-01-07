md_merchant_get_list()
{


	char base_str[1024],url[50],getmerchantNum[30],u_name[20];

	strcpy(u_name,lr_eval_string(mendian_loginName()));
	lr_save_string(u_name,"u_name");

	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	strcpy(base_str,lr_eval_string("{\"login_name\":\"{u_name}\"}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
	//lr_output_message("Base64: %s", lr_eval_string("{base_str}"));

	web_reg_find("Text=\"code\":0","Savecount=merchant_get_list_code_count",LAST);//设置检查点
	/**
	 * {"code":0,"message":"成功","merchant_list":[{"merchant_id":100109,"merchant_name":"华凌八季鲜"}]}
	 */
	//微商登录商家ID做关联
	web_reg_save_param("merchantid","RB=\,","LB={\"merchant_id\":","ORD=ALL",LAST);//用关联函数取值 
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("merchant_get_list");
	web_custom_request("merchant_get_list",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=master.data.merchant.get.list&sid=&sign=&params={base_str}",
		LAST);
     if(atoi(lr_eval_string("{merchant_get_list_code_count}"))>0){
			lr_end_transaction("merchant_get_list",LR_PASS);
		}else{
            lr_end_transaction("merchant_get_list",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
	//多个商家时随机取值
	sprintf(getmerchantNum,"{merchantid_%d}",rand()%(atoi(lr_eval_string("{merchantid_count}")))+1);
	lr_save_string (lr_eval_string(getmerchantNum),"merchantid_value" );
	return 0;
}
