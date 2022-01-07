zd_temp_pur_audit()
/**
 * 集单审核操作
 */
{
	
	char base_str1[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
	lr_save_string(url,"url");


	strcpy(base_str1,lr_eval_string("{\"pre_po_num_id\":{zd_pre_po_num_id}}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");


	web_reg_find("Text=\"code\":0","Savecount=pur_audit_code_count",LAST);//设置检查点

	web_add_header("Authorization","{zd_author}");
    web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("temp_pur_audit");
	web_custom_request("temp_pur_audit",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.pre.po.audit&sid={zd_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{pur_audit_code_count}"))>0){
			lr_end_transaction("temp_pur_audit",LR_PASS);
		}else{
			lr_end_transaction("temp_pur_audit",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
    
	return 0;
}
