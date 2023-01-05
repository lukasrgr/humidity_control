import { JsonRpcRequest } from "./jsonrpc";
import { format } from 'date-fns';

export class GetLatestDataRequest extends JsonRpcRequest {

    static METHOD: string = "getLatestData";
    public constructor(
    ) {
        super(GetLatestDataRequest.METHOD, {})
    }
}