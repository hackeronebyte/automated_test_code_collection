md_author_confirm()
/**
 * 确认制单4步
 */
{
    char base_str1[500],base_str2[500],base_str3[500],base_str4[500],itemid_or_barcode[20],supply_unit_num_id[20];

	//获取固定代理商ID supply_unit_num_id
	strcpy(supply_unit_num_id,lr_eval_string(mendian_supply_unit_num_id()));
	lr_save_string(supply_unit_num_id,"supply_unit_num_id");;
    //获取固定代理商的固定商品ID
	strcpy(itemid_or_barcode,lr_eval_string(mendian_itemid_barcode()));
	lr_save_string(itemid_or_barcode,"itemid_or_barcode");

    //确认制单1
    strcpy(base_str1,lr_eval_string("{\"type_num_id\":1,\"remark\":\"\","
									"\"supply_unit_num_id\":{supply_unit_num_id},"
									"\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"apply_logistics_type\":0,\"apply_num_id\":\"{md_sequence_num}\","
									"\"div_num_id\":0,\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=confirm_apply_hdr_save_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_hdr_save");
    web_custom_request("apply_hdr_save",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.hdr.save&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{confirm_apply_hdr_save_code_count}"))>0){
			lr_end_transaction("apply_hdr_save",LR_PASS);
		}else{
            lr_end_transaction("apply_hdr_save",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

	//确认制单2
    strcpy(base_str2,lr_eval_string("{\"qty\":1{dayhour}.0,"
									"\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"package_qty\":1{dayhour}.0,\"pmt_qty\":0.0,"
									"\"series\":\"{md_series}\",\"apply_num_id\":\"{md_sequence_num}\","
									"\"item_num_id\":{itemid_or_barcode},\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=confirm_apply_dtl_save_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_dtl_save");
    web_custom_request("apply_dtl_save",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.dtl.save&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{confirm_apply_dtl_save_code_count}"))>0){
			lr_end_transaction("apply_dtl_save",LR_PASS);
		}else{
            lr_end_transaction("apply_dtl_save",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

    //确认制单3
    strcpy(base_str3,lr_eval_string("{\"apply_num_id\":\"{md_sequence_num}\","
									"\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str3,"base_str3");
	strcpy(base_str3,base64_encode(lr_eval_string("{base_str3}"),strlen(base_str3)));
	lr_save_string(base_str3,"base_str3");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=by_author_confirm_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("by_author_confirm");
    web_custom_request("by_author_confirm",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.by.author.confirm&sid={md_sid}&sign=&params={base_str3}",
		LAST);
	if(atoi(lr_eval_string("{by_author_confirm_code_count}"))>0){
			lr_end_transaction("by_author_confirm",LR_PASS);
		}else{
            lr_end_transaction("by_author_confirm",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

     //确认制单4
    strcpy(base_str4,lr_eval_string("{\"sql_id\":\"LDPPAY-0001\","
									"\"on_line\":true,\"input_param\":"
									"{\"apply_num_id\":\"{md_sequence_num}\"},"
									"\"page_num\":1,\"page_size\":1000}"));
	lr_save_string(base_str4,"base_str4");
	strcpy(base_str4,base64_encode(lr_eval_string("{base_str4}"),strlen(base_str4)));
	lr_save_string(base_str4,"base_str4");// 编码base64
	web_reg_find("Text=\"code\":0","Savecount=by_comfirm_data_export_code_count",LAST);//设置检查点
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("md_author_confirm-LDPPAY-0001");
    web_custom_request("by_comfirm_data_export",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str4}",
		LAST);
	if(atoi(lr_eval_string("{by_comfirm_data_export_code_count}"))>0){
			lr_end_transaction("md_author_confirm-LDPPAY-0001",LR_PASS);
		}else{
            lr_end_transaction("md_author_confirm-LDPPAY-0001",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}


	return 0;
}
