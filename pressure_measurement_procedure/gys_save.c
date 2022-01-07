gys_save()
/**
 * 代理商保存 供三步
 */
{
    //保存第一步
	char base_str1[1024],base_str2[1024],base_str3[1024],url[50];
	strcpy(url,lr_eval_string(gys_base_url("/gateway")));
    lr_save_string(url,"url");



	strcpy(base_str1,lr_eval_string("{\"update_bl_pos\":[{\"series\":\"{gys_series}\","
									"\"po_num_id\":\"{gys_po_num_id}\","
									"\"sup_produce_date\":null,\"sup_confirm_total_qty\":{gys_sup_confirm_total_qty}}]}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=gys_savel_code_count",LAST);//设置检查点
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("udpateScmBlPoSupDtl");
	web_custom_request("gys_savel",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=com.ykcloud.soa.PPAY.scm.service.impl.purchase.udpateScmBlPoSupDtl&params={base_str1}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_savel_code_count}"))>0){
			lr_end_transaction("udpateScmBlPoSupDtl",LR_PASS);
		}else{
			lr_end_transaction("udpateScmBlPoSupDtl",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 


    //保存第二步
	strcpy(base_str2,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_034\","
									"\"input_param\":{\"supply_unit_num_id\":\"{gys_supply_unit_num_id}\"},"
									"\"data_sign\":\"0\",\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");
	web_reg_find("Text=\"code\":0","Savecount=gys_save2_code_count",LAST);//设置检查点
	lr_start_transaction("SUPPLIER_ORDER_034");
	web_custom_request("gys_save2",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str2}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_save2_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_034",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_034",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


    //保存第三步
	strcpy(base_str3,lr_eval_string("{\"sql_id\":\"YKPPAY-0056\",\"input_param\":{\"page_num\":1,"
									"\"page_size\":100},\"data_sign\":\"0\",\"tenant_num_id\":\"gysmerchantid_value\"}"));
	lr_convert_string_encoding(base_str3, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str3" );
	strcpy(base_str3,lr_eval_string("{base_str3}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");
	web_reg_find("Text=\"code\":0","Savecount=gys_save3_code_count",LAST);//设置检查点
	lr_start_transaction("YKPPAY-0056");
	web_custom_request("gys_save3",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str3}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_save3_code_count}"))>0){
			lr_end_transaction("YKPPAY-0056",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-0056",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	return 0;
}
