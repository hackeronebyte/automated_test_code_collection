zd_temp_pur()
/**
 * 手工集单
 */
{
    char base_str[1024],url[50];
    strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	
    strcpy(base_str,lr_eval_string("{}"));
    lr_convert_string_encoding(base_str, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str" );
    strcpy(base_str,lr_eval_string("{base_str}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
	web_reg_find("Text=\"code\":0","Savecount=merge_temp_pur_code_count",LAST);//设置检查点

	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("merge_temp_pur");
	web_custom_request("merge_temp_pur",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.merge.temp.pur&sid={zd_sid}&sign=&params={base_str}",
		LAST);
	if(atoi(lr_eval_string("{merge_temp_pur_code_count}"))>0){
			lr_end_transaction("merge_temp_pur",LR_PASS);
		}else{
			lr_end_transaction("merge_temp_pur",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

	return 0;
}
