gys_confirm()
/**
 *确认订单 后查询全部订单
 */
{

    //确认订单
	char base_str1[1024],base_str2[1024],url[50];
	strcpy(url,lr_eval_string(gys_base_url("/gateway")));
    lr_save_string(url,"url");

	strcpy(base_str1,lr_eval_string("{\"user_num_id\":\"{user_num_id}\","
									"\"sub_unit_num_id\":{gys_sub_unit_num_id},\"order_date\":\"{gys_order_date}\","
									"\"po_num_id\":\"{gys_po_num_id}\",\"sup_confirm_date\":\"{gys_order_date}\"}"));
	lr_convert_string_encoding(base_str1, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str1" );
	strcpy(base_str1,lr_eval_string("{base_str1}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");
	web_reg_find("Text=\"code\":0","Savecount=gys_confirm_code_count",LAST);//设置检查点
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("gys_date_confirm");
	web_custom_request("gys_confirm",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=ykcloud.scm.purchase.order.delivery.date.confirm&params={base_str1}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_confirm_code_count}"))>0){
			lr_end_transaction("gys_date_confirm",LR_PASS);
		}else{
			lr_end_transaction("gys_date_confirm",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 


    //再次查询全部
    strcpy(base_str2,lr_eval_string("{\"sql_id\":\"SUPPLIER_ORDER_001\","
									"\"input_param\":{\"supply_unit_num_id\":\"{supply_unit_num_id}\","
									"\"po_num_id\":\"\",\"begin_dtme\":\"2021-12-01\",\"end_dtme\":\"{today}\","
									"\"approval_num_id\":\"\",\"status_num_id\":\"2\","
									"\"po_type_id\":\"\",\"logistics_type\":\"\"},\"page_num\":1,"
									"\"page_size\":10,\"data_sign\":\"0\",\"tenant_num_id\":\"{gysmerchantid_value}\"}"));
	lr_convert_string_encoding(base_str2, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str2" );
	strcpy(base_str2,lr_eval_string("{base_str2}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");

	web_reg_find("Text=\"code\":0","Savecount=gys_cgd_query_all_again_code_count",LAST);//设置检查点
	lr_start_transaction("SUPPLIER_ORDER_001");
	web_custom_request("ggys_cgd_query_all_again",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=method=hg.poykl.data.export&params={base_str2}&sid={gys_sid}&timestamp={timestamp}&sign=",
		LAST);
	if(atoi(lr_eval_string("{gys_cgd_query_all_again_code_count}"))>0){
			lr_end_transaction("SUPPLIER_ORDER_001",LR_PASS);
		}else{
			lr_end_transaction("SUPPLIER_ORDER_001",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
	return 0;
}
