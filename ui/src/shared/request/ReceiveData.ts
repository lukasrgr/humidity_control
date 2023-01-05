import { JsonRpcRequest } from "./jsonrpc";
import { format } from 'date-fns';

export class ReceiveDataRequest extends JsonRpcRequest {

    // static METHOD: string = "getLatestData";
    // public constructor(
    //     private fromDate: Date,
    //     private toDate: Date,
    // ) {
    //     super(ReceiveDataRequest.METHOD, {
    //         fromDate: format(fromDate, 'yyyy-MM-dd'),
    //         toDate: format(toDate, 'yyyy-MM-dd'),
    //     });
    // }
}