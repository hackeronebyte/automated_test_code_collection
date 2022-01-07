md_ysd_sh()
/**
 * 微商验收单收货
 */
{
    char base_str1[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//微商保存第一步
	strcpy(base_str1,lr_eval_string("{\"reserved_no\":\"{md_ysd_reserved_no}\",\"sub_unit_num_id\":{md_sub_unit_num_id},\"receipt_sign\":\"1\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_receipt_finish_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("md_ysd_receipt_finish");
	web_custom_request("md_ysd_receipt_finish",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykl.kvm.receipt.finish&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_receipt_finish_code_count}"))>0){
			lr_end_transaction("md_ysd_receipt_finish",LR_PASS);
		}else{
			lr_end_transaction("md_ysd_receipt_finish",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
	return 0;
}
