function Get-WindowsUpdateStatus {
    <#
    .SYNOPSIS
    Checks the current Windows Update pause status.
    
    .OUTPUTS
    System.String
    Returns enabled or disabled
    #>
    
    $registryPath = "HKLM:\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings"
    $pauseKeys = @("PauseFeatureUpdatesStartTime","PauseQualityUpdatesStartTime","PauseUpdatesStartTime","PauseFeatureUpdatesEndTime","PauseQualityUpdatesEndTime","PauseUpdatesExpiryTime")
    $pauseStatus = @{}
    
    foreach ($key in $pauseKeys) {
        $value = Get-ItemProperty -Path $registryPath -Name $key -ErrorAction SilentlyContinue
        if ($value) {
            $pauseStatus[$key] = $value.$key
        } else {
            $pauseStatus[$key] = "Not Set"
        }
    }
    
    $updateStatus = "Enabled"
    $now = Get-Date
    $activeKeys = $pauseStatus.Keys | Where-Object { $pauseStatus[$_] -ne "Not Set" }
    
    if ($activeKeys) {
        foreach ($key in $activeKeys) {
            if ($key -like "*StartTime") {
                $timestamp = [datetime]::Parse($pauseStatus[$key])
                $endKey = $key -replace "StartTime","EndTime"
                
                if ($pauseStatus[$endKey] -and $pauseStatus[$endKey] -ne "Not Set") {
                    $endTime = [datetime]::Parse($pauseStatus[$endKey])
                    if ($now -ge $timestamp -and $now -le $endTime) {
                        $updateStatus = "Disabled"
                        break
                    }
                }
            }
        }
    }
    
    return $updateStatus
}



function Pause-WindowsUpdate {
    <#
    .SYNOPSIS
    Pauses Windows Update for a specified duration.
    
    .PARAMETER Hours
    The number of hours to pause Windows Update.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [int]$Hours
    )
    
    $registryPath = "HKLM:\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings"
    
    # Get current UTC time
    $startTime = [datetime]::UtcNow
    $endTime = $startTime.AddHours($Hours)
    
    # Convert to ISO 8601 format string (2026-01-15T07:20:14Z)
    $startTimeStr = $startTime.ToString("yyyy-MM-ddTHH:mm:ssZ")
    $endTimeStr = $endTime.ToString("yyyy-MM-ddTHH:mm:ssZ")
    
    try {
        # Set Start times
        Set-ItemProperty -Path $registryPath -Name "PauseFeatureUpdatesStartTime" -Value $startTimeStr
        Set-ItemProperty -Path $registryPath -Name "PauseQualityUpdatesStartTime" -Value $startTimeStr
        Set-ItemProperty -Path $registryPath -Name "PauseUpdatesStartTime" -Value $startTimeStr
        
        # Set End times
        Set-ItemProperty -Path $registryPath -Name "PauseFeatureUpdatesEndTime" -Value $endTimeStr
        Set-ItemProperty -Path $registryPath -Name "PauseQualityUpdatesEndTime" -Value $endTimeStr
        Set-ItemProperty -Path $registryPath -Name "PauseUpdatesExpiryTime" -Value $endTimeStr
        
        Write-Host ("Windows Update paused for " + $Hours + " hours (until " + $endTimeStr + " UTC)")
    }
    catch {
        Write-Error ("Failed to pause Windows Update: " + $_)
    }
}

function Resume-WindowsUpdate {
    <#
    .SYNOPSIS
    Resumes Windows Update by removing pause registry keys.
    #>
    
    $registryPath = "HKLM:\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings"
    $pauseKeys = @("PauseFeatureUpdatesStartTime", "PauseQualityUpdatesStartTime", "PauseUpdatesStartTime", "PauseFeatureUpdatesEndTime", "PauseQualityUpdatesEndTime", "PauseUpdatesExpiryTime")
    
    try {
        foreach ($key in $pauseKeys) {
            Remove-ItemProperty -Path $registryPath -Name $key -ErrorAction SilentlyContinue
        }
        Write-Host "Windows Update resumed successfully"
    }
    catch {
        Write-Error ("Failed to resume Windows Update: " + $_)
    }
}

