gys_sendStoreSmsCode()
/**
 * ģ�ⷢ�Ͷ���
 */
{
    char base_str1[1024],url[50];
	strcpy(url,lr_eval_string(gys_base_url("/system/sendStoreSmsCode")));
    lr_save_string(url,"url");


	web_reg_find("Text=\"code\":0","Savecount=sendStore_code_count",LAST);//���ü���


	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("sendStore");
	//{\"username\":\"s{supply_unit_num_id}\",\"tenantNumId\":\"{gysmerchantid_value}\"}
	web_custom_request("sendStore",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/json",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/json",
		"Body={\"username\":\"s{supply_unit_num_id}\",\"tenantNumId\":\"{gysmerchantid_value}\"}",
		LAST);
	if(atoi(lr_eval_string("{sendStore_code_count}"))>0){
			lr_end_transaction("sendStore",LR_PASS);
		}else{
			lr_end_transaction("sendStore",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	return 0;
}
