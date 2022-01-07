zd_merchant_get_list()
{

    char base_str[1024],url[50],getmerchantNumzd[30],zd_u_name[20];
	//获取总商登录名
	strcpy(zd_u_name,lr_eval_string(zongdian_loginName()));
	//将汉字转为utf-8
	lr_convert_string_encoding(zd_u_name, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"zd_u_name" );
    strcpy(zd_u_name,lr_eval_string("{zd_u_name}"));
	lr_save_string(zd_u_name,"zd_u_name");
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

   
      

	strcpy(base_str,lr_eval_string("{\"login_name\":\"{zd_u_name}\"}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
	//lr_output_message("Base64: %s", lr_eval_string("{base_str}"));

	web_reg_find("Text=\"code\":0","Savecount=zdmerchant_get_list_code_count",LAST);//设置检查点
	/**
	 * {"code":0,"message":"成功","full_message":null,
	 "merchant_list":[{"merchant_id":201101,"merchant_name":"微商服务店"}]}
	 */
	//关联获取总商商户ID
	web_reg_save_param("zdmerchantid","RB=\,","LB={\"merchant_id\":","ORD=ALL",LAST);//用关联函数取值 
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
     if(atoi(lr_eval_string("{zdmerchant_get_list_code_count}"))>0){
			lr_end_transaction("merchant_get_list",LR_PASS);
		}else{
            lr_end_transaction("merchant_get_list",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
    //随机总商商户ID
	sprintf(getmerchantNumzd,"{zdmerchantid_%d}",rand()%(atoi(lr_eval_string("{zdmerchantid_count}")))+1);
	lr_save_string (lr_eval_string(getmerchantNumzd),"zd_merchantid_value" );
	return 0;
}
