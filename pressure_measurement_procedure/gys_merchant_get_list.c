gys_merchant_get_list()
/**
 * 代理商获取商户信息
 */
{

    char base_str1[1024],url[50],getmerchantNumgys[10];
	strcpy(url,lr_eval_string(gys_base_url("/omp_cmanage/gateway")));
    lr_save_string(url,"url");


	strcpy(base_str1,lr_eval_string("{\"login_name\":\"s{supply_unit_num_id}\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");


	web_reg_find("Text=\"code\":0","Savecount=gys_merchant_get_list_code_count",LAST);//设置检查点

    //代理商商家ID
	/**
	 * {"code":0,"message":"成功","merchant_list":[{"merchant_name":"华凌八季鲜","merchant_id":100109}]}
	 */
	web_reg_save_param("gysmerchantid","RB=}","LB=\"merchant_id\":","ORD=ALL",LAST);//用关联函数取值 

	
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("gys_merchant_get_list");
	web_custom_request("gys_merchant_get_list",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=master.data.merchant.get.list&params={base_str1}&app_key=13000&timestamp={timestamp}&data_sign=0&tenant_num_id=&sid=&sign=bafa0ea5ae8c3f8785cfa2c6a770c6a9f7e14069",
		LAST);
	if(atoi(lr_eval_string("{gys_merchant_get_list_code_count}"))>0){
			lr_end_transaction("gys_merchant_get_list",LR_PASS);
		}else{
			lr_end_transaction("gys_merchant_get_list",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
	sprintf(getmerchantNumgys,"{gysmerchantid_%d}",rand()%(atoi(lr_eval_string("{gysmerchantid_count}")))+1);
	lr_save_string (lr_eval_string(getmerchantNumgys),"gysmerchantid_value" );
	return 0;
}
