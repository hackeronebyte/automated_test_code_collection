md_ysd_save()
/**
 * 微商验收单保存 四步
 * 
 */
{
    char base_str1[1024],base_str2[1024],base_str3[1024],base_str4[1024],base_str5[1024],url[50];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//微商保存第一步
	strcpy(base_str1,lr_eval_string("{\"reserved_no\":\"{md_ysd_reserved_no}\",\"sub_unit_num_id\":{md_sub_unit_num_id},\"car_temperature\":0.0,\"remark\":\"\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_temperature_update_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("md_ysd_temperature_update");
	web_custom_request("md_ysd_temperature_update",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykl.kvm.receipt.car.temperature.update&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_temperature_update_code_count}"))>0){
			lr_end_transaction("md_ysd_temperature_update",LR_PASS);
		}else{
			lr_end_transaction("md_ysd_temperature_update",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商保存第二步
    strcpy(base_str2,lr_eval_string("{\"sub_unit_num_id\":{md_sub_unit_num_id},\"reserved_no\":\"{md_ysd_reserved_no}\",\"receipt_dtl_infos_list\":[{\"series\":\"{md_ysd_series}\",\"item_num_id\":{md_ysd_item_num_id},\"actual_production_date\":\"\",\"package_qty\":{md_ysd_package_qty},\"confirm_all_qty\":{md_ysd_package_qty}}]}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_updateConfirmallqty_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("md_ysd_updateConfirmallqty");
	web_custom_request("md_ysd_updateConfirmallqty",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykl.kvm.receipt.updateConfirmallqty&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_updateConfirmallqty_code_count}"))>0){
			lr_end_transaction("md_ysd_updateConfirmallqty",LR_PASS);
		}else{
			lr_end_transaction("md_ysd_updateConfirmallqty",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商保存第三步 md_ysd_fh_series 关联参数action(md_ysd_query)
    strcpy(base_str3,lr_eval_string("{\"series\":\"{md_ysd_fh_series}\",\"reserved_no\":\"{md_ysd_reserved_no}\",\"po_num_id\":\"0\"}"));
	lr_convert_string_encoding(base_str3, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str3" );
	strcpy(base_str3,lr_eval_string("{base_str3}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_st3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");
	web_reg_find("Text=\"code\":0","Savecount=md_ysd_bill_update_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("md_ysd_bill_update");
	web_custom_request("md_ysd_bill_update",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykl.kvm.receipt.bill.update&sid={md_sid}&sign=&params={base_st3}",
		LAST);
	if(atoi(lr_eval_string("{md_ysd_bill_update_code_count}"))>0){
			lr_end_transaction("md_ysd_bill_update",LR_PASS);
		}else{
			lr_end_transaction("md_ysd_bill_update",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商保存第四步 md_ysd_reserved_no 关联action(md_ysd_query)
    strcpy(base_str4,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-0305-1\",\"on_line\":true,\"input_param\":{\"reserved_no\":\"{md_ysd_reserved_no}\"},\"page_num\":1,\"page_size\":0}"));
	lr_convert_string_encoding(base_str4, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str4" );
	strcpy(base_str4,lr_eval_string("{base_str4}"));
	lr_save_string(base_str4,"base_str4");
	strcpy(base_str4,base64_encode(lr_eval_string("{base_str4}"),strlen(base_str4)));
	lr_save_string(base_str4,"base_str4");
	web_reg_find("Text=\"code\":0","Savecount=YKPPAY-WM-0305-1_code_count",LAST);//设置检查点
   
	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("YKPPAY-WM-0305-1");
	web_custom_request("YKPPAY-WM-0305-1",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str4}",
		LAST);
	if(atoi(lr_eval_string("{YKPPAY-WM-0305-1_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-0305-1",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-0305-1",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//微商保存第五步
	strcpy(base_str5,lr_eval_string("{\"sql_id\":\"YKPPAY-WM-0340\",\"on_line\":true,\"input_param\":{\"reserved_no\":\"{md_ysd_reserved_no}\",\"head_sub_unit_num_id\":\"{zd_sub_unit_num_id}\",\"po_num_id\":\"0\"},\"page_num\":1,\"page_size\":1000}"));
	lr_convert_string_encoding(base_str5, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str5" );
	strcpy(base_str5,lr_eval_string("{base_str5}"));
	lr_save_string(base_str5,"base_str5");
	strcpy(base_str5,base64_encode(lr_eval_string("{base_str5}"),strlen(base_str5)));
	lr_save_string(base_str5,"base_str5");
	web_reg_find("Text=\"code\":0","Savecount=YKPPAY-WM-0340_code_count",LAST);//设置检查点

	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("YKPPAY-WM-0340");
	web_custom_request("YKPPAY-WM-0340",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str5}",
		LAST);
	if(atoi(lr_eval_string("{YKPPAY-WM-0340_code_count}"))>0){
			lr_end_transaction("YKPPAY-WM-0340",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-WM-0340",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	return 0;
}
