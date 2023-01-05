import { format } from 'date-fns';
import { JsonRpcRequest } from './jsonrpc';

/**
 * <pre>
 * {
 *   "jsonrpc": "2.0",
 *   "id": UUID,
 *   "method": "queryHistoricData",
 *   "params": {
 *      "setupPassword": string
 *   }
 * }
 * </pre>
 */
export class QueryHistoricDataRequest extends JsonRpcRequest {

    static METHOD: string = "queryHistoricData";

    public constructor(
        fromDate: Date,
        toDate: Date,
    ) {
        super(QueryHistoricDataRequest.METHOD, {
            fromDate: format(fromDate, 'yyyy-MM-dd HH:mm:ss'),
            toDate: format(toDate, 'yyyy-MM-dd HH:mm:ss'),
        })
    }

}